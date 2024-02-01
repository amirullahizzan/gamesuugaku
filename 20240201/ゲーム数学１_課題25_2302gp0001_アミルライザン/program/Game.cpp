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

//	ミニマップ画像用の変数
int mini_map_image;		//	ミニマップの背景画像
int mini_player_image;	//	ミニプレイヤー
int mini_npc_image;		//	ミニＮＰＣ

int mapMode = 0;

//	ミニマップの基準の座標
Float2 center_map;		//	３Ｄ空間の原点を中心にしたミニマップの中心座標
Float2 player_map;		//	プレイヤーが中心のミニマップ

const int MAP_SIZE = 200;
const int MAP_SIZE_HALF = MAP_SIZE * 0.5;

Float2 mapIndicatorPos = { 16,64 };

bool isAnimationMode = false;
int animationMode = 0;
int mapInfoMode = 0;

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
	//	ミニマップ画像の読み込み
	mini_map_image = LoadGraph( "data/mini_map.bmp" );			//	ミニマップの背景画像
	mini_player_image = LoadGraph( "data/mini_player.bmp" );	//	ミニプレイヤー
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );			//	ミニＮＰＣ
	//	それぞれのミニマップの中心座標
	center_map.set( 120.0f, 330.0f );	//	センターマップ
	player_map.set( 0.0f - MAP_SIZE_HALF, 330.0f );	//	プレイヤーマップ
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------


void GameUpdate()
{
	ground.Update();
	//	左右キーで向きを変えて上キーで移動
	player.Update();

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		animationMode = 1;
		if (mapMode == 0)
		{ 
			mapIndicatorPos = { mapIndicatorPos.x,80 }; 
		}
		else
		{
			mapIndicatorPos = { mapIndicatorPos.x,64 };
		}
	}

	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	プレイヤー座標オッ渡してカメラの設定
	camera.Update( player.m_pos );
}

void MapAreaFocus()
{
	//	センターマップの描画
//---------------------------------------------
//	半透明の設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//	センターマップの背景画像の描画
	DrawRotaGraphF(center_map.x, center_map.y, 1.0f, TO_RADIAN(0.0f), mini_map_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	ミニＮＰＣの描画
	for (int i = 0; i < NPC_MAX; i++) {
		float nx = center_map.x + npc[i].m_pos.x * 10.0f;
		float ny = center_map.y - npc[i].m_pos.z * 10.0f;
		DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, TRUE);
	}

	//	プレイヤーの３Ｄ座標を２Ｄにしてマップに描画
	//	Ｘ座標：センターマップの中心から、３ＤのＸ座標を１０倍したところ
	float px = center_map.x + player.m_pos.x * 10.0f;
	//	Ｙ座標：３Ｄの奥が２Ｄの下になってしまうので逆方向に
	float py = center_map.y - player.m_pos.z * 10.0f;
	//	この座標がミニマップ内の時だけ
	if (px > center_map.x - 100.0f && px < center_map.x + 100.0f) {
		if (py > center_map.y - 100.0f && py < center_map.y + 100.0f) {
			//	この座標でミニプレイヤー画像の描画（画像の向きはモデルのＹ軸の回転を使って）
			DrawRotaGraphF(px, py, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, TRUE);
		}
	}
}

void MapPlayerFocus()
{
	//---------------------------------------------
//	プレイヤーマップの描画
//---------------------------------------------
//	プレイヤーマップの背景画像の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRotaGraphF(player_map.x, player_map.y, 1.0f, TO_RADIAN(0.0f), mini_map_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	ミニＮＰＣの描画
	for (int i = 0; i < NPC_MAX; i++) {
		//	プレイヤーから見た時にＮＰＣがどの方向にいるかを使って座標を決めます
		float nx = player_map.x + (npc[i].m_pos.x - player.m_pos.x) * 10.0f;
		float ny = player_map.y - (npc[i].m_pos.z - player.m_pos.z) * 10.0f;
		//	この座標がミニマップの範囲外だったら描画処理をしないでループを次へ
		if (nx < player_map.x - 100.0f)	continue;
		if (nx > player_map.x + 100.0f)	continue;
		if (ny < player_map.y - 100.0f)	continue;
		if (ny > player_map.y + 100.0f)	continue;
		//	描画処理
		DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, TRUE);
	}

	//	ミニプレイヤーの描画（常にミニマップの中心、向きは３Ｄプレイヤーの向きに合わせる）
	DrawRotaGraphF(player_map.x, player_map.y, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, TRUE);
}


//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	３Ｄ描画のためのカメラの設定
	camera.Render();
	//	それぞれのモデルの描画
	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	//	ミニマップの描画
	//---------------------------------------------
	Float2 animPos;
	Float2 animPos2;

	
	clsDx();
	//printfDx(" centermap %f", center_map.x);
	//printfDx(" playermap %f", player_map.x);
	printfDx(" mapindi %f", mapIndicatorPos.y);
	const float animSpeed = 5.2f;
	static int fontsize_half = GetFontSize() * 0.5f;
	DrawCircle(mapIndicatorPos.x, mapIndicatorPos.y + fontsize_half, 6, COLOR_YELLOW, 1);

	switch (mapMode)
	{
	case 0:
		MapAreaFocus();
		//DrawCircle(16, 64 + fontsize_half, 6, COLOR_YELLOW, 1);

		if (center_map.x + MAP_SIZE_HALF > 0 && animationMode == 1)
		{
			animPos.x -= animSpeed;
		}
		else if (center_map.x <= 120.0f && animationMode == 2)
		{
			animPos.x += animSpeed;
		}
		else
		{
			animationMode = 0;
		}

		if (center_map.x + MAP_SIZE_HALF <= 0)
		{
			mapMode = 1;
			animationMode = 2;
		}
		center_map.x += animPos.x;

		break;

	case 1:
		MapPlayerFocus();

		if (player_map.x + MAP_SIZE_HALF > 0 && animationMode == 1)
		{
			animPos2.x -= animSpeed;
		}
		else if (player_map.x <= 120.0f && animationMode == 2)
		{
			animPos2.x += animSpeed;
		}
		else
		{
			animationMode = 0;
		}

		if (player_map.x + MAP_SIZE_HALF <= 0)
		{
			mapMode = 0;
			animationMode = 2;
		}
		player_map.x += animPos2.x;
		break;
	}

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "どちらかのミニマップを画面左下に表示", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "スペースキー：ミニマップの切り替え", GetColor( 255, 255, 0 ) );

	

	DrawString( 16, 64, "　３Ｄの原点が中心のミニマップ", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "　プレイヤーが中心のミニマップ", GetColor( 255, 255, 0 ) );


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
