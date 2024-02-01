#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	モデルデータ用の変数
int ground_model;
int player_model;
int npc_model;
//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;
//	ＮＰＣクラスは複数宣言
#define NPC_MAX	8
Npc		npc[NPC_MAX];

int mini_map_image;
int mini_player_image;
int mini_npc_image;

Float2 center_map;
Float2 player_map;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	モデルデータ番号を渡してクラスの初期化
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );

	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}

	mini_map_image = LoadGraph( "data/mini_map.bmp" );
	mini_player_image = LoadGraph( "data/mini_player.bmp" );
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );

	center_map.set( 120.0f, 330.0f );
	player_map.set( 680.0f, 330.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	player.Update();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}

	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//clsDx();
	//printfDx("player Z pos : %f", player.m_pos.z);
	//	３Ｄ描画のためのカメラの設定
	camera.Render();
	//	それぞれのモデルの描画
	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	//CENTER MINIMAP
	{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraphF(center_map.x, center_map.y, 1, 0, mini_map_image, 1);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		for (int i = 0; i < NPC_MAX; i++) {
			float nx = center_map.x + (npc[i].m_pos.x * 10);
			float ny = center_map.y + (npc[i].m_pos.z * 10 * -1);
			DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, 1);
		}

		const int MainAreaSize = 10;
		float px = center_map.x + player.m_pos.x * MainAreaSize;
		float py = center_map.y + player.m_pos.z * MainAreaSize * -1;
		if (player.m_pos.x < 10.0f && player.m_pos.x > -10.0f && player.m_pos.z > -10.0f && player.m_pos.z < 10.0f)
		{
			DrawRotaGraphF(px, py, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, 1);
		}
	}

	//PLAYER FOCUSED MINIMAP
	{
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraphF(player_map.x, player_map.y, 1.0f, 0, mini_map_image, 1);
		DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		for (int i = 0; i < NPC_MAX; i++) 
		{
			const int MAIN_AREA_SIZE = 10;
			float nx =  (player.m_pos.x*MAIN_AREA_SIZE * -1) + player_map.x + (npc[i].m_pos.x * 10);
			float ny =  (player.m_pos.z*MAIN_AREA_SIZE) + player_map.y + (npc[i].m_pos.z * 10 * -1);
			const int MAP_SIZE = 200;
			if (nx < player_map.x - (MAP_SIZE * 0.5) ) continue;
			if (nx > player_map.x + (MAP_SIZE * 0.5) ) continue;
			if (ny < player_map.y - (MAP_SIZE * 0.5) ) continue; 
			if (ny > player_map.y + (MAP_SIZE * 0.5) ) continue;
			DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, 1);
		}

		float px = player_map.x;//*player.m_pos.x;
		float py = player_map.y;//*player.m_pos.y;
		DrawRotaGraphF(px, py, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, 1);
		
	}

	
	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );

	DrawString(   0, 210, "３Ｄの原点が中心のミニマップ", GetColor( 255, 255, 255 ) );
	DrawString( 560, 210, "プレイヤーが中心のミニマップ", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );

	camera.Exit();
	ground.Exit();
	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	DeleteGraph( mini_map_image );
	DeleteGraph( mini_player_image );
	DeleteGraph( mini_npc_image );
}
