#include "Main.h"
#include "Game.h"

//	プレイヤー画像用の変数
#define GROUND_Y 300

int player_image;
//	プレイヤー座標
float player_x;
float player_y;
//	プレイヤーの移動スピード用の変数
float player_speed;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込みと初期座標の設定
	player_image = LoadGraph( "data/player.bmp" );
	//	float 型の変数に数値を設定するので、float と分かるように後ろに f を付けてます
	player_x = 100.0f;
	player_y = 100.0f;
	//	初期スピード
	player_speed = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player_x-=2;
	}
	else if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		player_x+=2;
	}


	//	スピード変数の値を常に増やしていきます

	player_y += player_speed;

	//	プレイヤーの座標移動（縦方向に移動させたいのでＹ座標を変更します）

	if (player_y < GROUND_Y-0.3f)
	{
		player_speed += 0.3f;

	}
	else
	{
		player_speed = 0;
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			player_speed = -10;
		}
	}
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤーの描画（描画するための座標が float 型なので）
	DrawGraphF( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "画面下に落下移動（スピードを増やしながら下移動）", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "画面下に消えないように適当なところでＹ座標を止める", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "スペース：ジャンプ（画面上方向に移動量を設定）", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}
