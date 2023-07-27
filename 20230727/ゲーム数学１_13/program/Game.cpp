#include "Main.h"
#include "Game.h"
#include "Hit.h"

#define PLAYER_SPEED	 3.0f
#define NPC_SPEED		 3.0f
#define MISSILE_SPEED	10.0f

#define NPC_SIZE		50.0f
#define MISSILE_SIZE	20.0f
#define MISSILE_MAX		100

int player_image;
float player_x;
float player_y;

int npc_image;
float npc_x;
float npc_y;

int missile_image;
float missile_x[MISSILE_MAX];
float missile_y[MISSILE_MAX];

bool isMissileMode[MISSILE_MAX];


void GameInit()
{

	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 700.0f;
	npc_y = 300.0f;

	missile_image = LoadGraph( "data/missile.bmp" );
	for (int i = 0;i < MISSILE_MAX;i++)
	{
		isMissileMode[i] = false;
		missile_x[i] = 0.0f;
		missile_y[i] = 0.0f;
	}
	
}




void MoveMissile(int i)
{
		missile_x[i] += 5;
		if (missile_x[i] > SCREEN_W)
		{
			isMissileMode[i] = false;
		}
	
}


void HoldMissile(int i)
{
		missile_x[i] = player_x + 50 / 3;
		missile_y[i] = player_y + 50 / 3;
}

void RandomizeNpc()
{
	npc_x = SCREEN_W ;
	npc_y = GetRand(300 - NPC_SIZE) + NPC_SIZE;
}



void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < MISSILE_MAX; i++)
		{

			if (!isMissileMode[i])
			{
				isMissileMode[i] = true;
				break;
			}
			//continues to the second 

		}
	}


	for (int i = 0; i < MISSILE_MAX; i++)
	{
		if (!isMissileMode[i])
		{
			HoldMissile(i);
		}

	if (isMissileMode[i])
	{
			MoveMissile(i);
			if (CheckBoxHit(missile_x[i], missile_y[i], MISSILE_SIZE, MISSILE_SIZE, npc_x, npc_y, NPC_SIZE, NPC_SIZE))
			{
				RandomizeNpc();
				isMissileMode[i] = false;
			}
	}
	
	}


	npc_x -= NPC_SPEED;
	if( npc_x < -NPC_SIZE )
	{
		npc_x = SCREEN_W;
	}
}




void GameRender()
{
	for (int i = 0; i < MISSILE_MAX; i++)
	{
		DrawGraphF(missile_x[i], missile_y[i], missile_image, TRUE);
	}

	DrawGraphF( npc_x, npc_y, npc_image, TRUE );

	DrawGraphF( player_x, player_y, player_image, TRUE );

	

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "スペース：ミサイル発射", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "→　スペースキーを押すたびに１発撃ちます", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( missile_image );
}
