#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"

//	プレイヤー・ＮＰＣの半径（当たり判定で使います）
#define CHARA_RADIUS	25.0f

//	プレイヤーの移動スピード
#define PLAYER_SPEED	5.0f

#define BAR_X 600
//	プレイヤー変数
int		player_image;	//	画像
Float2	player_pos;		//	座標
int		player_hp;		//	ＨＰ
int		player_hp_bar;		//	ＨＰ
int		player_hp_display;		//	ＨＰ
int immune_delay = 0;
const int MAX_PLAYER_HP = 5;
int bar_color_i = 0;

//	ＮＰＣの移動スピード
#define NPC_SPEED		3.0f
//	ＮＰＣ変数
int		npc_image;		//	画像
Float2	npc_pos;		//	座標

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_pos.x = 100.0f;
	player_pos.y = 200.0f;
	//	ＨＰ５で開始
	player_hp = 5;

	npc_pos.x = 500.0f;
	npc_pos.y = 300.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーでプレイヤー移動
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_pos.x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_pos.x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_pos.y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_pos.y -= PLAYER_SPEED;

	//	ＮＰＣの移動処理
	npc_pos.x -= NPC_SPEED;
	if( npc_pos.x < 0.0f ){
		npc_pos.x = SCREEN_W;
		npc_pos.y = GetRand( SCREEN_H );
	}
	const int HP_BAR_WIDTH = 500;

		immune_delay--; 
		if (immune_delay <= 0) { immune_delay = 0; }
	//	プレイヤーとＮＰＣが当たったら
	if( CheckCircleHit( player_pos, CHARA_RADIUS, npc_pos, CHARA_RADIUS ) ){
		//	ＨＰを１減らす
		if (immune_delay<=0)
		{
			player_hp -= 1;
			if (player_hp <= 0)
			{
			player_hp = 0;
			}
			immune_delay = 50;
			player_hp_bar+= HP_BAR_WIDTH / MAX_PLAYER_HP;
			
		}
	}
	if (player_hp_display > player_hp_bar)
	{
		player_hp_display--;
		
	}
	else if (player_hp_display < player_hp_bar)
	{
		player_hp_display++;
	}

	if (player_hp_display >= HP_BAR_WIDTH)
	{
		player_hp_display = HP_BAR_WIDTH;
	}

	if (player_hp_display < HP_BAR_WIDTH/2)
	{

		bar_color_i = 0;
	}
	else
	{
		bar_color_i = 1;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの描画
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( 180.0f ), npc_image, TRUE );

	int bar_color[2];
	bar_color [0] = GetColor(0,255,0);
	bar_color [1] = GetColor(255,0,0);

	//	プレイヤーの描画
	if (immune_delay % 3 == 0 || immune_delay == 0)
	{
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );
	}

	//	ＨＰバーの白い枠の四角（Ｘ座標 100 ～ 600 で幅を 500 にしています）
	//int barpoint = player_hp % BAR_X;
	DrawFillBox(100,100, BAR_X- player_hp_display,120,bar_color[bar_color_i]);
	DrawLineBox( 100, 100, BAR_X, 120, GetColor( 255, 255, 255 ) );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "プレイヤーとＮＰＣが当たったらＨＰが１減る（でも敵は消えない）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "→　プレイヤーは当たった後一定時間点滅（その間は無敵）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "ＨＰに合わせたバーを四角を使って描画", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "→　バーの長さが半分以下の時は色を変える", GetColor( 255, 255, 0 ) );

	//	ＨＰを文字列で描画
	DrawFormatString( 16, 103, GetColor( 0, 255, 255 ), "ＨＰ：%d", player_hp );

	clsDx();
	printfDx("%d",player_hp_display);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
