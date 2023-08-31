#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f
//	ＮＰＣの移動スピード
#define NPC_SPEED		2.0f
//	それぞれの半径
#define RADIUS			25.0f

//	プレイヤー用の変数
int player_image;		//	画像
float player_x;			//	Ｘ座標
float player_y;			//	Ｙ座標
float player_rot;		//	向き（角度の度）

//	ＮＰＣも
int npc_image;
float npc_x;
float npc_y;
float npc_rot;		//	回転するので角度用の変数（度）

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込みと初期座標の設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;
	//	右向きから開始（右向き：０度）
	player_rot = 0.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 500.0f;
	npc_y = 300.0f;
	npc_rot = 0.0f;
}

int game_frame = 0;
int npc_facing = 0;
int npc_facing_previous = 0;
int facing_timer_rand = 1;

void NPCAI()
{
	enum 
	{
		DOWN = 0, LEFT = 1, UP= 2, RIGHT = 3
	};

	if (game_frame % (facing_timer_rand) == 0)
	{
		facing_timer_rand = 10 * (GetRand(10)+1);
		npc_facing = GetRand(3);
		while(npc_facing == npc_facing_previous)
		{
			npc_facing = GetRand(3);
			break;
		}
		npc_facing_previous = npc_facing;
	}
		switch (npc_facing)
		{
		case DOWN:
			npc_rot = 90.0f;
			npc_y+=NPC_SPEED;
			break;
		case LEFT:
			npc_rot = 180.0f;
			npc_x-= NPC_SPEED;
			break;
		case UP:
			npc_rot = 270.0f;
			npc_y-= NPC_SPEED;
			break;
		case RIGHT:
			npc_rot = 0.0f;
			npc_x += NPC_SPEED;
			break;
		}
}

void GameUpdate()
{
	game_frame++;

	NPCAI();
	//	十字キーで座標移動（ついでに向きも変える）
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		//	右向きにしたいので０度
		player_rot = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		//	左向きは１８０度
		player_rot = 180.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		//	下向きにしたいので９０度
		player_rot = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		//	上向き：２７０度
//		player_rot = 270.0f;
		//	上向き：ー９０度
		player_rot = -90.0f;
	}

	if (npc_x > SCREEN_W)
	{
		npc_x = 0;
	}
	if (npc_x < 0 )
	{
		npc_x = SCREEN_W;
	}
	if (npc_y > SCREEN_H)
	{
		npc_y = 0;
	}
	if (npc_y < 0)
	{
		npc_y = SCREEN_H;
	}
		
	//	今回はＮＰＣの常に回転の処理は入れていません


	//	プレイヤーとＮＰＣで当たり判定（円同士で）
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		//	当たったらＮＰＣの座標を画面内のどこかランダムに設定
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = (float)GetRand( SCREEN_H );
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	座標と向きを設定できる描画関数を使います

	
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	//	プレイヤーの向き player_rot（度） をラジアン角に変換 TO_RADIAN して描画関数に渡します
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "ＮＰＣはプレイヤーと当たると座標再設定", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "ＮＰＣは適当な時間たったらランダムに向きを変える", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "→　上下左右に向きを変えて上下左右に移動", GetColor( 255, 255, 0 ) );
	DrawFormatString(20, 280, GetColor(255, 255, 120), "Facing : %d", npc_facing);
	DrawFormatString(20, 300, GetColor(255, 255, 120), "Facing Timer : %d", facing_timer_rand);

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	//	読み込んだ画像の終了処理
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
