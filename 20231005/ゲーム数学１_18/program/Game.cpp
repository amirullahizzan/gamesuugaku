#include "Main.h"
#include "Game.h"
#include "Hit.h"

//プレイヤーの移動スピード
#define PLAYER_SPEED	3.0f
//　ＮＰＣ　の移動スピードすぐにプレイヤーのところにいかないように少しゆっくりにしています
#define NPC_SPEED		1.0f
//あたり判定で使うのでプレイヤーとNPCの半径
#define CHARA_RADIUS	25.0f

int player_image;
float player_x;
float player_y;
float player_rot;


int npc_image;
float npc_x;
float npc_y;
float npc_rot;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_x = 150.0f;
	player_y = 200.0f;
	//右向きで開始
	player_rot = 0.0f;

	npc_x = 500.0f;
	npc_y = 300.0f;
	npc_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int playertomouse_dist = 0;
float mouse_x = 0;
float mouse_y = 0;
float dx = 0;
float dy = 0;
float radian = 0;
void GameUpdate()
{
	//
	mouse_x = GetMouseX();
	mouse_y = GetMouseY();
	float dx = mouse_x-player_x;
	float dy = mouse_y - player_y ;
	//playertomouse_dist = GetDistance(player_x,player_y, mouse_x, mouse_y);
	
	/*if (dx > 0)
	{
		player_x++;
	}
	else if (dx < 0)
	{
		player_x--;
	}*/


	if (!CheckCircleHit(player_x,player_y,CHARA_RADIUS,mouse_x,mouse_y, 0) )
	{
	float mov_x = PLAYER_SPEED * cosf(TO_RADIAN(player_rot));
	float mov_y = PLAYER_SPEED * sinf(TO_RADIAN(player_rot));
	player_x += mov_x;
	player_y += mov_y;
	}


	 //radiance = GetRadian_LengthYX(dy,dx); //Get an Arc Tan from dx dy
	radian = atan2f(dy,dx);
		//player_y += cosf(TO_RADIAN(playertomouse_dist) );
	player_rot = TO_DEGREE(radian);
	
	float nx = player_x - npc_x;
	float ny = player_y - npc_y;
	float npc_radian = atan2f(ny, nx);
	float npcmov_x = PLAYER_SPEED * cosf(TO_RADIAN(npc_rot));
	float npcmov_y = PLAYER_SPEED * sinf(TO_RADIAN(npc_rot));
	npc_x += npcmov_x;
	npc_y += npcmov_y;
	
	npc_rot = TO_DEGREE(npc_radian);

	//プレイヤーとＮＰＣの当たり判定（円同士で）
	if( CheckCircleHit( player_x, player_y, CHARA_RADIUS, npc_x, npc_y, CHARA_RADIUS ) ){
		npc_x = GetRand( SCREEN_W );
		npc_y = GetRand( SCREEN_H );
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx(); //reset printfdx everytime called
	printfDx("player radian : %7.2f\n", radian);
	printfDx("player rotation : %7.2f\n", player_rot);

	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );
		
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 16, 16, "プレイヤー：マウスに向かって移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "ＮＰＣ　　：プレイヤーに向かって移動", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
