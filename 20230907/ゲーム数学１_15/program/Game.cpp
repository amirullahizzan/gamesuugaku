#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define PLAYER_MOV_SPEED	5.0f
#define PLAYER_ROT_SPEED	3.0f

int player_image;
float player_x;
float player_y;
float player_rot;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;
	player_rot = 0.0f;
}

//Tank Control

void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_rot+=PLAYER_ROT_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_rot-= PLAYER_ROT_SPEED;
	}

	if( CheckHitKey( KEY_INPUT_UP ) )
	{
		//cos();
		// need two of parameters to move the tank, x and y

		player_x+= cosf(TO_RADIAN(player_rot)) * PLAYER_MOV_SPEED; // Adjacent //mult by 1 by default
		player_y+= sinf(TO_RADIAN(player_rot)) * PLAYER_MOV_SPEED; // Opposite

		//float x = GetLength_RotSotte(TO_RADIAN(player_rot)); // Adjacent
		//float y = GetLength_RotMukai(TO_RADIAN(player_rot)); // Opposite
		//player_x += x;
		//player_y += y;

		//minus is on left and up, just like the original pos of x and y
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawFormatString(20, 60, GetColor(255, 255, 0), "COS : %f", cosf(TO_RADIAN(player_rot)));
	DrawFormatString(20, 80, GetColor(255, 255, 0), "SIN : %f", sinf(TO_RADIAN(player_rot)));
	DrawFormatString(20, 100, GetColor(255, 255, 0), "TAN : %f", tanf(TO_RADIAN(player_rot)));
	DrawFormatString(20, 140, GetColor(255, 255, 0), "Rot : %f", player_rot);


}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}
