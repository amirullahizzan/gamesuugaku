#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define NPC_RADIUS		25.0f
#define MISSILE_RADIUS	10.0f

float missile_x;
float missile_y;

float npc_x;
float npc_y;

float dx;
float dy;
float dist;

void GameInit()
{
	missile_x = 50.0f;
	missile_y = SCREEN_H / 2.0f;

	npc_x = SCREEN_W;
	npc_y = 350.0f;
}

bool launch_player = false;

void ResetMissile()
{
	launch_player = false;
	missile_x = 50.0f;
}

void ResetEnemy()
{
	npc_x = SCREEN_W + NPC_RADIUS;
	npc_y = (float)GetRand(SCREEN_H);
}

void ResetScene()
{
	ResetMissile();
	ResetEnemy();
}

void GameUpdate()
{
	if (!launch_player)
	{
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			missile_y += 3.0f;
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			missile_y -= 3.0f;
		}
	}

	if( PushHitKey( KEY_INPUT_SPACE ) )
	{
		launch_player = true;
	}
	if (launch_player)
	{
		missile_x+=15;
	}

	npc_x -= 3.0f;
	if( npc_x < -NPC_RADIUS )
	{
		ResetEnemy();
	}
	if (missile_x > SCREEN_W+MISSILE_RADIUS)
	{
		ResetMissile();
	}

	/*dx = missile_x - npc_x;
	dy = missile_y - npc_y;
	dist = (float)sqrt((dx * dx) + (dy * dy));*/

	if (CheckCircleHit(missile_x, missile_y, MISSILE_RADIUS, npc_x, npc_y, NPC_RADIUS))
	{
		ResetScene();
	}

}

void GameRender()
{
	DrawCircle( npc_x, npc_y, NPC_RADIUS, GetColor( 255, 128, 128 ) );

	DrawCircle( missile_x, missile_y, MISSILE_RADIUS, GetColor( 128, 255, 128 ) );

	DrawString( 20,  20, "上下キー：緑色のミサイル円の上下移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "スペース：ミサイル円の横移動開始", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "赤いＮＰＣ円とミサイル円が当たるとそれぞれ座標再設定", GetColor( 255, 255, 255 ) );
}


void GameExit()
{
}
