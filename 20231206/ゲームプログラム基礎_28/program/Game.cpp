#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"
#include "BG.h"

//	データ用の変数
int bg_image;		//	背景用
int player_image;	//	プレイヤー
int npc_image;		//	ＮＰＣ

//	クラスの宣言
BG		bg;			//	背景
Player	player;		//	プレイヤー
Npc		npc;		//	ＮＰＣ

float camera_x = 0;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	データの読み込み
	bg_image = LoadGraph( "data/bg.bmp" ); //3000 x 450
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	読み込んだデータを渡して初期化
	bg.Init( bg_image );
	player.Init( player_image );
	npc.Init( npc_image );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	クラスの更新処理
	bg.Update();
	player.Update();
	npc.Update();

	float player_screen_x = player.m_pos.x - camera_x;
	if (player_screen_x > X_RIGHT)
	{
		float x = player_screen_x - X_RIGHT;
		camera_x += x;
	}
	else if (player_screen_x < X_LEFT)
	{
		float x = player_screen_x - X_LEFT;
		camera_x += x;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	//	クラスの描画処理
	bg.Render(camera_x);
	npc.Render(camera_x);
	player.Render(camera_x);

	DrawLine( X_RIGHT, 0, X_RIGHT, SCREEN_H, GetColor( 0, 255, 255 ) );

	DrawString( 16, 16, "左右キー：プレイヤーの移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　プレイヤーは水色の線より右に行かない（代わりに他が動く感じ）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "スペース：ジャンプ", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	
	bg.Exit();
	player.Exit();
	npc.Exit();

	DeleteGraph( bg_image );
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
