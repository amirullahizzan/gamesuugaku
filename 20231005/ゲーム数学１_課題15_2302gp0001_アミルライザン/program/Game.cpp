#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f
//	今回は目標の座標に向きが変わるので回転スピードはありません

//	ＮＰＣの移動スピード（少し遅めにしています）

//	当たり判定で使うのでプレイヤーとＮＰＣの半径
#define CHARA_RADIUS	25.0f
//	円の半径
#define CIRCLE_RADIUS	50.0f
//	プレイヤー用の変数
int player_image;	//	画像
float player_x;		//	Ｘ座標
float player_y;		//	Ｙ座標
float player_rot;	//	向き（度：目標座標に向くようにします）
//	ＮＰＣ用の変数
int npc_image;
int npctarget[5];

const int MAX_NPC = 5;
float NPC_SPEED[MAX_NPC];
float npc_x[MAX_NPC];
float npc_y[MAX_NPC];
float npc_rot[MAX_NPC];

//	円
float circle_x;			//	Ｘ座標
float circle_y;			//	Ｙ座標

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_x = 150.0f;
	player_y = 200.0f;
	//	最初は０度（右向き）で開始
	player_rot = 0.0f;

	for (int i = 0; i < MAX_NPC; i++)
	{
		npctarget[i] = 0;
		npc_x[i] = (float)GetRand(500.0f);
		npc_y[i] = (float)GetRand(300.0f);
		npc_rot[i] = 0.0f;
		NPC_SPEED[i] = GetRand(5)+ 2;
	}

	circle_x = 700.0f;
	circle_y = 0.0f;
}

float px = 0;
float py = 0;
float nx = 0;
float ny = 0;

enum PlayerTargetEnum
{
	ToNPC = 0, ToBall = 1
};

void GameUpdate()
{
	//	プレイヤーをマウスの方に向かわせる
	//	１：目標座標（マウス座標）を取得
	float mouse_x = GetMouseX();
	float mouse_y = GetMouseY();
	//	２：今の座標（プレイヤー座標）から目標座標（マウス座標）までどのくらいか

	px = mouse_x - player_x;
	py = mouse_y - player_y;
	//	３：その値を使って角度を求める（ GetRadian_LengthYX：y x を渡すとラジアン角がもらえる関数）
	float radian = GetRadian_LengthYX( py, px );
	//	上で取得した角度はラジアン角なので、この角度を「度」にしてプレイヤーの角度変数に渡します
	//	TO_DEGREE：ラジアン角を「度」に変換する関数
	player_rot = TO_DEGREE( radian );

	//	このままだとプレイヤーがマウス座標のところを行ったり来たりを繰り返してしまうので
	//	プレイヤーがマウスにあたっていないときだけ移動するようにします
	if( CheckPointCircleHit( mouse_x, mouse_y, player_x, player_y, CHARA_RADIUS ) == false ){
		//	４：プレイヤーの向きが決まったのでその方向に座標移動させます
		//	PLAYER_SPEED をプレイヤーの向きに合わせてＸ方向とＹ方向に分けます
		//	その分座標移動させます
		float mov_x = PLAYER_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		float mov_y = PLAYER_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
		if (player_x > SCREEN_W/2)
		{
			player_x = SCREEN_W/2;
		}
		player_x += mov_x;
		player_y += mov_y;
	}

	//	円の移動
	circle_y += 1.0f;
	if( circle_y > SCREEN_H ){
		circle_y = 0.0f;
	}
	
	for (int i = 0; i < MAX_NPC; i++)
	{
		switch (npctarget[i])
		{
		case ToNPC:
			nx = player_x - npc_x[i];
			ny = player_y - npc_y[i];
			if (CheckCircleHit(player_x, player_y, CHARA_RADIUS, npc_x[i], npc_y[i], CHARA_RADIUS))
			{
				NPC_SPEED[i] = GetRand(5) + 2;
				npctarget[i] = ToBall;
			}
			break;
		case ToBall:
			nx = circle_x - npc_x[i];
			ny = circle_y - npc_y[i];
			if (CheckCircleHit(npc_x[i], npc_y[i], CHARA_RADIUS, circle_x, circle_y, CIRCLE_RADIUS))
			{
				NPC_SPEED[i] = GetRand(5) + 2;
				npctarget[i] = ToNPC;
			}
			break;
		}

		//	ＮＰＣはプレイヤーに向かって移動する
		//	ＮＰＣから見てプレイヤーがどれだけ進んだ先にあるか
		//	その値を使って角度を求める（ GetRadian_LengthYX から取得したラジアン角を「度」に変換して npc_rot に渡します）
		npc_rot[i] = TO_DEGREE(GetRadian_LengthYX(ny, nx));
		//	ＮＰＣの向きが決まったのでその方向に移動させます（移動量を求めてそれを座標に足します）
		npc_x[i] += NPC_SPEED[i] * GetLength_RotSotte(TO_RADIAN(npc_rot[i]));
		npc_y[i] += NPC_SPEED[i] * GetLength_RotMukai(TO_RADIAN(npc_rot[i]));
	}
	//	プレイヤーとＮＰＣの当たり判定（円同士で）

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("player x : %f",player_x);
	//	プレイヤー移動範囲の描画
	DrawFillBox( 0, 0, SCREEN_W / 2, SCREEN_H, GetColor( 0, 64, 128 ) );
	//	円の描画
	DrawCircleAA( circle_x, circle_y, CIRCLE_RADIUS, 30, GetColor( 255, 255, 255 ) );

	for (int i = 0;i < MAX_NPC;i++)
	{
	DrawRotaGraphF( npc_x[i], npc_y[i], 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 16, 16, "プレイヤー：マウスに向かって移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　移動範囲は画面左側（右の円と距離を取りたいので）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "ＮＰＣ　　：プレイヤーに向かって移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "→　プレイヤーに当たったら円に向かう", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "→　円に当たったらプレイヤーに向かう", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "→　当たるたびに向かう先を切り替える", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
