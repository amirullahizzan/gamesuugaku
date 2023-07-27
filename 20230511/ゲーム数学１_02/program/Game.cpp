#include "Main.h"
#include "Game.h"
#include "../Control.h"
#include "../Init.h"


int player_image;
int npc_image;

int playerx = 0;
int playery = 0;
double playerrotation = 0;
int enemyx = 0;
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	LoadBMP();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------

void GameUpdate()
{
	PlayerControl();
	enemyx--;
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		enemyx = 0;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	
	DrawRotaGraph(200 + playerx, 100,1,playerrotation, player_image, TRUE,0);
	//DrawGraph( 200+playerx, 100, player_image, TRUE );
	DrawGraph( 500+enemyx, 300, npc_image, TRUE );

	DrawString( 20, 20, "←→キー：プレイヤー移動（画面外にはいかない）", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "スペース：ＮＰＣの座標の設定", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
