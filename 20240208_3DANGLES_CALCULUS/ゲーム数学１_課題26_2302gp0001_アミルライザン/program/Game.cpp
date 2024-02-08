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
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	//	クラスの初期化
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc[i].Init(npc_model);
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------

void RandomizePos(Float3 &pos, Float3 &rot)
{
	int randSpot = GetRand(4);
	float corner_rotation_mult = 90.0f;
	switch (randSpot)
	{
	case 0:
		pos.z = 10.0f; pos.x = -10.0f;
		rot.y = GetRandomF(corner_rotation_mult*1, corner_rotation_mult*2);
		break;

	case 1:
		pos.z = 10.0f; pos.x = 10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 2, corner_rotation_mult * 3);
		break;

	case 2:
		pos.z = -10.0f; pos.x = -10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 4, corner_rotation_mult * 5);
		break;

	case 3:
		pos.z = -10.0f; pos.x = 10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 3, corner_rotation_mult * 4);
		break;
	}
}
void GameUpdate()
{
	ground.Update();
	//	左右キーで回転・上キーで移動
	player.Update();

	//	プレイヤーの方に徐々に向きを変えながら移動する（なのでプレイヤー座標を渡します）
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc[i].Update(player.m_pos);

		//	それぞれの座標の更新が終わりましたので球同士で当たり判定をします
		if (CheckBallHit(player.m_pos, CHARA_RADIUS, npc[i].m_pos, CHARA_RADIUS)) {
			//	ＮＰＣの座標をランダムに（原点から地面の四角プラスマイナス１個分）
			//npc[i].m_pos.z = GetRandomF(-10.0f, 10.0f);
			//npc[i].m_pos.x = GetRandomF(-10.0f, 10.0f);
			//npc[i].m_rot.y = GetRandomF(0.0f, 360.0f);

			RandomizePos(npc[i].m_pos,npc[i].m_rot);
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

	DrawString(16, 16, "十字キー：プレイヤー回転・移動", GetColor(255, 255, 255));
	DrawString(16, 32, "ＮＰＣはプレイヤーの方に向きを変えながら移動", GetColor(255, 255, 255));
	DrawString(16, 48, "プレイヤーとＮＰＣで当たり判定　→　当たったらＮＰＣの座標をランダムに設定", GetColor(255, 255, 255));
	DrawString(16, 64, "ＮＰＣを複数にする（初期向きをランダムに）", GetColor(255, 255, 0));
	DrawString(16, 80, "ＮＰＣ再設定座標は黄色い領域の「左下・左上・右上・右下」のどれか", GetColor(255, 255, 0));
	DrawString(16, 96, "→　向きもその登場場所から黄色い領域内に向かってランダムな向きに", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
	MV1DeleteModel(npc_model);

	camera.Exit();
	ground.Exit();
	player.Exit();
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Exit();
	}
}
