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
class Area : public Base
{
public:
	void Init() 
	{
		m_pos.set(AREA_X_MAX - AREA_X_MIN, 0.0f, AREA_Z_MAX - AREA_Z_MIN);
		m_rot.set(0.0f, 0.0f, 0.0f);
		m_size.set(AREA_X_MIN, 0.5f, AREA_Z_MIN);
	}
};
Area area;
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
	area.Init();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	クラスの更新処理
	ground.Update();
	//	十字キーで座標移動
	player.Update();
	//	特に何もしていません
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	プレイヤーとＮＰＣで当たり判定
	for( int i = 0; i < NPC_MAX; i++ ){
		//	ボックス同士で当たり判定
		if( CheckBoxHit3D( player.m_pos, player.m_size, npc[i].m_pos, npc[i].m_size ) ){
			//	当たったらＮＰＣの座標をランダムに設定
			npc[i].SetRandom();
		}
	}

	//	プレイヤー座標を渡してカメラの更新処理を呼びます


	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void ForceCam()
{
	//	カメラの見る座標の高さは地面の高さに
	camera.m_look.y = 0.0f;

	//	カメラ座標は見る座標から一定離れたところ
	camera.m_look.x = (AREA_X_MIN + AREA_X_MAX) / 2;
	camera.m_look.z = (AREA_Z_MIN + AREA_Z_MAX) / 2;
	camera.m_pos.x = camera.m_look.x + 0.0f;
	camera.m_pos.y = camera.m_look.y + 9.0f;
	camera.m_pos.z = camera.m_look.z - 10.0f;
}

int m_lastcammode = 0;
void GameRender()
{
	clsDx();
	printfDx("player x: %f\n\n",player.m_pos.x);
	printfDx("player x: %f\n\n",player.m_pos.y);
	printfDx("player x: %f\n\n",player.m_pos.z);

	printfDx("area x: %f\n",area.m_pos.x);
	printfDx("area x: %f\n", area.m_pos.y);
	printfDx("area x: %f\n", area.m_pos.z);

	printfDx("size x: %f\n",area.m_size.x);
	printfDx("size x: %f\n", area.m_size.y);
	printfDx("size x: %f\n", area.m_size.z);
	VECTOR vector = {area.m_pos.x,area.m_pos.y,area.m_pos.z};
	VECTOR vector2 = {area.m_size.x,area.m_size.y,area.m_size.z};

	printfDx("size x: %f\n", vector.x);
	printfDx("size x: %f\n", vector.y);
	printfDx("size x: %f\n", vector.z);
	DxLib::DrawCube3D(vector,vector2,GetColor(0,0,0), GetColor(0, 0, 0),1);
	if (CheckBoxHit3D(player.m_pos, player.m_size, area.m_pos, area.m_size)	)
	{
		ForceCam();
		//exit(0);
	}
	
	camera.Render();
	//	地面モデルの描画とステージ範囲の線の描画
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

	DrawString( 16, 112, "プレイヤーが四角のエリアに入るとエリアカメラに", GetColor( 0, 255, 255 ) );

	DrawString( 16, 128, "ＮＰＣもＸ方向移動（外枠に当たったら移動量の反転）", GetColor( 0, 255, 255 ) );
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
