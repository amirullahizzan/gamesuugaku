#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

#define CHARA_RADIUS 0.5f

int ground_model;
int player_model;
int npc_model;

Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	player.Update();
	npc.Update();

	camera.Update();

	

	if (CheckBoxHit3D
	(npc.m_pos, npc.GetModelSize(), player.m_pos, player.GetModelSize())
		)
	{
		float randomParam = 10;
		npc.m_pos = 
			Float3
			(GetRandomF(-randomParam, randomParam), 
				0, 
				GetRandomF(-randomParam, randomParam)
			);

		npc.ScaleModel(1.3f);
		player.ScaleModel(1.3f);
	}

	player.ShrinkModel(0.001f);
	npc.ShrinkModel(0.001f);
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "↑　キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "プレイヤーとＮＰＣで当たり判定　→　当たったらＮＰＣの座標をランダムに設定", GetColor( 255, 255, 255 ) );
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
	npc.Exit();
}
