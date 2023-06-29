#include "Main.h"
#include "Game.h"

int player_image;
int player_x;
int player_y;

int npc_image;
int npc_x;
int npc_y;

int item_image;
int item_x;
int item_y;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
int CheckPointBoxHit( int point_x, int point_y, int box_x, int box_y, int box_w, int box_h )
{
	if( point_x >= box_x && point_x <= box_x + box_w ){
		if( point_y >= box_y && point_y <= box_y + box_h ){
			return 1;
		}
	}

	return 0;
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 300;
	player_y = 100;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 400;
	npc_y = 200;

	item_image = LoadGraph( "data/item.bmp" );
	item_x = 500;
	item_y = 300;
}

void CheckTargetOnClick(int mouse_x,int mouse_y);
void ResetPos(int *x, int *y);

void GameUpdate()
{
	player_x -= 1;
	if( player_x < -50 ){
		player_x = 800;
		player_y = GetRand( 400 );
	}

	npc_x -= 2;
	if( npc_x < -50 ){
		npc_x = 800;
		npc_y = GetRand( 400 );
	}

	item_x -= 3;
	if( item_x < -50 ){
		item_x = 800;
		item_y = GetRand( 400 );
	}

	if( PushMouseInput() ){
		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();
		CheckTargetOnClick(mouse_x,mouse_y);
	}

	
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawGraph( item_x, item_y, item_image, TRUE );

	DrawGraph( npc_x, npc_y, npc_image, TRUE );

	DrawGraph( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "プレイヤー・ＮＰＣ・アイテムをマウスでクリック", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( item_image );
}

void CheckTargetOnClick(int mouse_x, int mouse_y)
{
	if (CheckPointBoxHit(mouse_x, mouse_y, player_x, player_y,  50,  50) )
	{
		ResetPos(&player_x, &player_y);
	}
	if (CheckPointBoxHit(mouse_x, mouse_y, npc_x, npc_y, 50, + 50) )
	{
		ResetPos(&npc_x, &npc_y);
	}
	if (CheckPointBoxHit(mouse_x, mouse_y, item_x, item_y,  50,  50) )
	{
		ResetPos(&item_x, &item_y);
	}
}

void ResetPos(int *x, int *y)
{
	*x = 800;
	*y = GetRand(400);
}