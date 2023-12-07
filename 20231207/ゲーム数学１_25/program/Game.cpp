#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	モデルデータの番号を入れる変数
int ground_model;
int player_model;
int npc_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;

#define NPC_MAX		5
Npc		npc[NPC_MAX];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	各モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	それぞれのクラスの初期化関数を呼ぶ
	//	カメラの初期化
	camera.Init();
	//	モデル番号を渡してそれぞれのクラスの初期化
	ground.Init( ground_model );
	player.Init( player_model );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	クラスの更新処理
	ground.Update();
	player.Update();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}

	for (int i =0; i < NPC_MAX;i++)
	{
		if (CheckBoxHit3D(player.m_pos,player.m_size,npc[i].m_pos, npc[i].m_size))
		{
			//do smth
			npc[i].SetRandom();
		}
	}

	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　外の枠に当たったら跳ね返るような動き", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "→　プレイヤーとＮＰＣで当たり判定（当たったらＮＰＣの座標をランダム設定）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "スペース：ジャンプ", GetColor( 255, 255, 255 ) );

	DrawString( 16, 80, "Ｆ１キー：全体カメラ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "Ｆ２キー：プレイヤーカメラ", GetColor( 255, 255, 255 ) );
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
}
