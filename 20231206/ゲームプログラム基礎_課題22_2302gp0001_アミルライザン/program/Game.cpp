#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"
#include "BG.h"

//	データ用の変数
int bg_image;		//	背景用
int player_image;	//	プレイヤー
int npc_image;		//	ＮＰＣ
//	「こういう感じで（時間があったら）.exe」用の画像用変数
int mini_player_image;	//	ミニプレイヤー画像

//	クラスの宣言
BG		bg;			//	背景
Player	player;		//	プレイヤー
Npc		npc;		//	ＮＰＣ

//	描画するために座標をどれだけずらすか
float game_offset_x;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	データの読み込み
	bg_image = LoadGraph( "data/bg.bmp" );			//	３０００ｘ４５０
	player_image = LoadGraph( "data/player.bmp" );	//	右向き
	npc_image = LoadGraph( "data/npc.bmp" );		//	左向き
	//	ミニプレイヤー画像の読み込み
	//	「こういう感じで（時間があったら）.exe」用に読み込みだけしています
	mini_player_image = LoadGraph( "data/mini_player.bmp" );

	//	読み込んだデータを渡して初期化
	bg.Init( bg_image );
	player.Init( player_image );
	npc.Init( npc_image );

	//	ずれは 0.0f から開始
	game_offset_x = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	クラスの更新処理
	bg.Update();		//	特に何もしない
	player.Update();	//	左右キーで横移動・スペースキーでジャンプ
	npc.Update();		//	特に何もしない

	//	今回の仕様としましては、基準の値（ X_RIGHT：画面座標）よりも
	//	プレイヤーの画面座標がどのくらい大きいかの判断になります
	//	というわけで、プレイヤーの画面座標を求めます
	float player_screen_x = player.m_pos.x - game_offset_x;
	//	この画面座標が基準座標を超えていたら
	if( player_screen_x > X_RIGHT ){
		//	どれだけ超えているか
		float x = player_screen_x - X_RIGHT;
		//	この分だけずれを増やします
		game_offset_x += x;
	}
	else if (player_screen_x < X_LEFT)
	{
		player.m_pos.x = game_offset_x + X_LEFT;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	クラスの描画処理（全て Base クラスの Render 関数を呼んでいます）
	//	どれだけずれたかを渡して描画関数を呼びます
	bg.Render( game_offset_x );
	npc.Render( game_offset_x );
	player.Render( game_offset_x );
	Float2 linepos;
	linepos.x = 20;
	linepos.y = 120;
	float player_initpos = 200.0f;
	const float initpos_miniplayer = 320 / player_initpos;
	DrawLine  (linepos.x												, linepos.y, 300 + 20, 120, GetColor(0,0,0), 1);
	DrawGraphF(linepos.x + game_offset_x * (300.0f / 3000.0f) + 20,	105	,mini_player_image,1);

	//	目安の線（プレイヤーはこれより左には移動しない）
	DrawLine( X_LEFT, 0, X_LEFT, SCREEN_H, GetColor( 255, 0, 0 ) );

	//	目安の線（プレイヤーがこれ以上右に行ったら周りが動く）
	DrawLine( X_RIGHT, 0, X_RIGHT, SCREEN_H, GetColor( 0, 255, 255 ) );

	DrawString( 16, 16, "左右キー：プレイヤーの移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　プレイヤーは水色の線より右に行かない（代わりに他が動く感じ）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "→　左移動は赤い線で止める", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "スペース：ジャンプ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "ＮＰＣは一定間隔でジャンプを繰り返す", GetColor( 255, 255, 0 ) );
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

	DeleteGraph( mini_player_image );
}
