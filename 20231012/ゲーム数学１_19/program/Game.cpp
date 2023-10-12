#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define CHARA_RADIUS	25.0f

int player_image;
Float2 player_pos;
float player_rot;
int player_traveled;

Float2 player_move;

int npc_image;
Float2 npc_pos;
float npc_rot;

Float2 mouse_pos;

Float2 ballpointer_pos;

bool isMousePressed = false;
bool isRetracting = false;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_pos.x = SCREEN_W / 2;
	player_pos.y = SCREEN_H / 2;
	player_rot = 0.0f;

	npc_pos.x = GetRand( SCREEN_W );
	npc_pos.y = GetRand( SCREEN_H );
	npc_rot = 0.0f;

}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{

	mouse_pos.x = GetMouseX();
	mouse_pos.y = GetMouseY();

	if( PushMouseInput() )
	{
		player_pos.x = mouse_pos.x;
		player_pos.y = mouse_pos.y;
	}
	

	if( CheckMouseInput() )
	{
		player_traveled = 0;

		isMousePressed = true;
		float dx = mouse_pos.x - player_pos.x;
		float dy = mouse_pos.y - player_pos.y;

		//player_rot = GetRadian_LengthYX(dy, dx); //already radian
		
		//player_rot = TO_DEGREE(atan2f(dy, dx));
		

		ballpointer_pos.x = mouse_pos.x;
		ballpointer_pos.y = mouse_pos.y;

		{
			//they stopped calculating when the mouse are released
			float dx = mouse_pos.x - player_pos.x;
			float dy = mouse_pos.y - player_pos.y;

			player_move.x = dx * 0.1;
			player_move.y = dy * 0.1;
			
			player_rot = atan2f(dy, dx) * 180.0f / 3.14159265f;
			//player_rot = atan2f(player_move.y, player_move.x) * 180.0f / 3.14159265f; //same

		}

	}
	else
	{
		isMousePressed = false;

		//player move is not yet calculated once
		player_pos.x += player_move.x;
		player_pos.y += player_move.y;
		player_traveled++;
		if (player_traveled > 120)
		{
			player_traveled = 0;
			player_move.x = 0;
			player_move.y = 0;
			player_pos.x = SCREEN_W / 2;
			player_pos.y = SCREEN_H/2;
		}
	}


	if ( CheckCircleHit(player_pos, CHARA_RADIUS,npc_pos, CHARA_RADIUS) )
	{
		npc_pos.x = GetRand(SCREEN_W);
		npc_pos.y = GetRand(SCREEN_H);
	}

	npc_rot+=0.2;


}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	if (isMousePressed)
	{
		DrawCircle(ballpointer_pos.x,ballpointer_pos.y,12,GetColor(255,255, 50),1);
		DrawLine(player_pos.x, player_pos.y, mouse_pos.x,mouse_pos.y , GetColor(255, 255, 50), 1);
	}

	DrawString( 16, 16, "マウスクリック：マウスの所にプレイヤーを置く", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "マウスドラッグ：プレイヤーはマウスの方を向く", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "→　プレイヤーとマウスを結んだ線を描画", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "マウスボタンを離したらプレイヤーは向いている方向に移動する", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "→　線が長いほど移動が速い", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "プレイヤーとＮＰＣで当たり判定", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
