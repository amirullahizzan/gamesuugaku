#include "Main.h"
#include "Game.h"
#include "Hit.h"

float player_speed = 3.0f;
#define IMAGESIZE 50
#define RADIUS 25

int player_image;
float player_x;
float player_y;

int npc_image;
float npc_x;
float npc_y;




double player_rotation = 0;
float npc_rotation = 0;
int game_frame = 0;

void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 500.0f;
	npc_y = 300.0f;
}

const float base_cooldown = 100;
float cooldown = 50;
float boostcapacity = 100;
bool isStartCooldown = false;

void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += player_speed;
		player_rotation = 0;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= player_speed;
		player_rotation = (180.0f);
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += player_speed;
		player_rotation = (90.0f);
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= player_speed;
		player_rotation = (270.0f);
	}

	if (CheckHitKey(KEY_INPUT_LSHIFT) && !isStartCooldown)
	{
		player_speed = 6;
		boostcapacity-=2;
	}
	else
	{
		if (boostcapacity < 100)
		{
			boostcapacity += 0.5f;
		}
		player_speed = 3.0f;
	}
	
	if (boostcapacity < 10)
	{
		isStartCooldown = true;
	}

	if (isStartCooldown)
	{

	cooldown--;
	if (cooldown <= 0)
	{
		cooldown = base_cooldown;
		isStartCooldown = false;
	}

	}

	game_frame++;
	//if (game_frame % 2 == 0) 
	npc_rotation+=(1);

	//if (CheckBoxHit(player_x,player_y,IMAGESIZE, IMAGESIZE,npc_x, npc_y,IMAGESIZE, IMAGESIZE))
	if(CheckCircleHit(player_x,player_y,RADIUS, npc_x, npc_y, RADIUS))
	{
		npc_x = (float)GetRand(SCREEN_W - IMAGESIZE)+IMAGESIZE;
		npc_y = (float)GetRand(SCREEN_H-IMAGESIZE) + IMAGESIZE;
	}

}


void GameRender()
{
	DrawRotaGraph(player_x, player_y, 1, TO_RADIAN(player_rotation), player_image, TRUE, FALSE, FALSE );
	DrawRotaGraph(npc_x, npc_y, 1, TO_RADIAN(npc_rotation), npc_image, TRUE, FALSE, FALSE);
	//DrawGraphF( npc_x, npc_y, npc_image, TRUE );
	//DrawGraphF( player_x, player_y, player_image, TRUE );

	DrawFormatString(20,400,GetColor(255,255,25)," Boost : %3.0f",boostcapacity);

	/*DrawCircle( 100, 100, 3, GetColor( 255, 255, 0 ) );
	DrawCircle( 500, 300, 3, GetColor( 255, 255, 0 ) );*/

	

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "ＮＰＣはプレイヤーと当たると座標再設定", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
