#include "Main.h"
#include "Game.h"
#include "Random.h"
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
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	//player_model = MV1LoadModel( "data/player.mqoz" );
	player_model = MV1LoadModel( "data/player2.mqoz" );
	//npc_model = MV1LoadModel( "data/npc.mqoz" );
	//MAGICA VOXEL SQUIDWARD
	npc_model = MV1LoadModel( "data/npc2.mqoz" );
	//	クラスの初期化
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
	//	左右キーで回転・上キーで移動
	player.Update();
	//	回転しているだけ
	npc.Update();

	camera.Update();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラの設定をして描画開始
	camera.Render();
	//	モデルの描画
	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "いつものプレイヤーモデルなどの表示を自作したモデルデータにしてみる", GetColor( 255, 255, 0 ) );
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
