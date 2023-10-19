#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//	ＮＰＣの最大数
#define NPC_MAX			5
//	ＮＰＣの移動スピード
#define NPC_MOV_SPEED	1.0f
//	ＮＰＣの回転スピード（度）：向きたい向きにこのスピードで回転していきます
#define NPC_ROT_SPEED	0.5f

//	当たり判定用の半径
#define NPC_RADIUS	25.0f

//	ＮＰＣの変数
int		npc_image;	//	画像
Float2	npc_pos[NPC_MAX];	//	座標
float	npc_rot[NPC_MAX];	//	向き（度）：この向きの値を目標の向きにしていく
int pos_sequencer = -1;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	npc_image = LoadGraph( "data/npc.bmp" );

	for (int i = 0;i<NPC_MAX;i++)
	{
	npc_pos[i].x= GetRand(500.0f);
	npc_pos[i].y= GetRand(350.0f);
	npc_rot[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	マウス座標（ＮＰＣが向かいたい座標）
	Float2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	１：今の座標（ npc_pos ）から目標座標（ mouse ）への向きを求める
	//	１－１：今の座標から目標座標までどのくらいか
	for (int i = 0; i < NPC_MAX; i++)
	{

	float x = mouse.x - npc_pos[i].x;
	float y = mouse.y - npc_pos[i].y;
	//	１－２：その値を使って向きを求める（この向きが最終的に向きたい向き）
	float goal_rot = TO_DEGREE( GetRadian_LengthYX( y, x ) );	//	GetRadian_LengthYX：atan2f

	//	２：今の向き（ npc_rot ）から目標の向き（ goal_rot ）までどのくらいの差（ next_rot ）があるか
	float next_rot = goal_rot - npc_rot[i];
	//	２－１：上で求めた角度の差を -180.0f ～ 180.0f にしたい
	//	１８０度を越えている分は１周分（３６０度）引く
	while( next_rot >= 180.0f )	next_rot -= 360.0f;
	while( next_rot < -180.0f )	next_rot += 360.0f;

	//	３：角度の差を見て回転させます（その差がプラスなら足していくマイナスなら引いていく）
	if( next_rot >= NPC_ROT_SPEED ){			//	プラス方向に回転スピード以上大きかったら
		npc_rot[i] += NPC_ROT_SPEED;				//	プラス回転させる
	}else if( next_rot <= -NPC_ROT_SPEED ){		//	回転スピードよりも左なら
		npc_rot[i] -= NPC_ROT_SPEED;				//	マイナス回転させる
	}else{										//	じゃない時（ほぼ正面の時）
		npc_rot[i] = goal_rot;						//	目標の向きにする
	}

	//	ＮＰＣの向いている方向に座標移動
	npc_pos[i].x += NPC_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( npc_rot[i]) );	//	GetLength_RotSotte：cosf
	npc_pos[i].y += NPC_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( npc_rot[i]) );	//	GetLength_RotMukai：sinf

	//	マウスとＮＰＣ（円として）で当たり判定（点と円の当たり判定）

	if( CheckPointCircleHit( mouse, npc_pos[i], NPC_RADIUS ) ){
		//	当たったら座標や向きをランダムに設定
		pos_sequencer++;
		switch (pos_sequencer)
		{
		case 0:
			npc_pos[i].x = 0;	//	0 ～ 800
			npc_pos[i].y = 0;	//	0 ～ 450
			npc_rot[i] = GetRand(90) + 90 -90;

			break;
		case 1:
			npc_pos[i].x = SCREEN_W;	//	0 ～ 800
			npc_pos[i].y = 0;	//	0 ～ 450
			npc_rot[i] = GetRand(90) + 90;

			break;
		case 2:
			npc_pos[i].x = SCREEN_W;	//	0 ～ 800
			npc_pos[i].y = SCREEN_H;	//	0 ～ 450
			npc_rot[i] = GetRand(90) + 180;

			break;
		case 3:
			npc_pos[i].x = 0;	//	0 ～ 800
			npc_pos[i].y = SCREEN_H;	//	0 ～ 450
			npc_rot[i] = GetRand(90) + 270;

			pos_sequencer = -1;
			break;
		}
		
	}

	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの描画
	for (int i = 0; i < NPC_MAX; i++)
	{
	DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	DrawString( 16, 16, "ＮＰＣはマウス座標に向かって移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　マウス座標と当たったら座標や向きの再設定", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "ＮＰＣは「一定の回転スピード」でマウス座標の方へ向きを変えながら移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "ＮＰＣ複数にする（初期座標や向きをランダムに）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "ＮＰＣ再設定座標は画面の「左上・右上・右下・左下」のどれか", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "→　向きもその登場場所から画面内に向かってランダムな向きに", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( npc_image );
}
