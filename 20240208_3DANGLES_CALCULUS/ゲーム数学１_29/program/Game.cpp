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
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
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
	npc.Update(player.m_pos);

	//	それぞれの座標の更新が終わりましたので球同士で当たり判定をします
	if( CheckBallHit( player.m_pos, CHARA_RADIUS, npc.m_pos, CHARA_RADIUS ) ){
		//	ＮＰＣの座標をランダムに
		npc.m_pos.x = GetRandomF( -10.0f, 10.0f );
		npc.m_pos.z = GetRandomF( -10.0f, 10.0f );
		//	向きも 0.0f ～ 360.0f のランダム
		npc.m_rot.y = GetRandomF( 360.0f );
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
	npc.Render();
	player.Render();

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "ＮＰＣはプレイヤーの方に向きを変えながら移動", GetColor( 255, 255, 255 ) );
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
