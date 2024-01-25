#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	キャラの半径
#define CHARA_RADIUS	0.5f
//	ＮＰＣの数
#define NPC_MAX		8

//	モデルデータ用の変数
int ground_model;
int player_model;
int npc_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;
Npc		npc[NPC_MAX];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	クラスの初期化（使うモデルデータを渡して）
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );

	for (int i = 0; i < NPC_MAX;i++)
	{
	npc[i].Init( npc_model );
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	左右キーで回転・上キーで移動
	player.Update();
	//	回転するだけ

	for (int i = 0; i < NPC_MAX;i++)
	{

		npc[i].Update();
		//	それぞれの座標の更新が終わりましたので球同士で当たり判定をします
		if (CheckBallHit(player.m_pos, CHARA_RADIUS, npc[i].m_pos, CHARA_RADIUS)) {
			//	ＮＰＣの座標をランダムに（原点から地面の四角プラスマイナス１個分）
			npc[i].m_pos.x = GetRandomF(-10.0f, 10.0f);
			npc[i].m_pos.z = GetRandomF(-10.0f, 10.0f);

			npc[i].ScaleModel(1.1f);
		}

	}
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
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "↑　キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "プレイヤーとＮＰＣで当たり判定　→　当たったらＮＰＣの座標をランダムに設定", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "ＮＰＣを複数にする", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "ＮＰＣも向いている方向に移動させる", GetColor( 255, 255, 0 ) );
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
	
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Exit();
	}
}
