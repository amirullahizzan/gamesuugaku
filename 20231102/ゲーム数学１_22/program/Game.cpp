#include "Main.h"
#include "Game.h"
#include "Random.h"
int player_model;
int npc_model;
int ground_model;
//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{

	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model    = MV1LoadModel("data/npc.mqoz");
}

float camrota = 0;
float camrotaver = 0;

struct Pos3
{
	float x = 0;
	float y = 0;
	float z = 0;
};

Pos3 campos = {0,10,-20};
Pos3 playerpos = { 5,0,0 };
Pos3 enemypos = {-5,0,0};
Pos3 enemyrota = {0,0,0};

void GameUpdate()
{
	//DxLib::SetCameraScreenCenter(0, 0);


	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//z -= 0.5f;
		//x += 0.5f;

		playerpos.x++;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//z += 0.5f;
		//x -= 0.5f;
		playerpos.x--;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//y -= 0.5f;
		//y += 0.5f;
		playerpos.z++;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		//y += 0.5f;
		//y -= 0.5f;
		playerpos.z--;
	}
		enemypos.z--;
		if (enemypos.z <= -20)
		{
			enemypos.z = 20;
			enemypos.x = GetRandomF(-10.0f, 20.0f);
		}

	if (CheckHitKey(KEY_INPUT_E)) {
		//camrota += 0.1f;
		enemyrota.x += 1.2f;
	}
	else if(CheckHitKey(KEY_INPUT_Q))
	{
		enemyrota.x -= 1.2f;
		//camrota -= 0.1f;
	}

	const int base_jumpcooldown = 60;
	static int jumpcooldown = 0;
	if (jumpcooldown > 0)
	{
		jumpcooldown--;
	}
	if (CheckHitKey(KEY_INPUT_SPACE) && jumpcooldown <= 0) {
		playerpos.y+=3;
		jumpcooldown = base_jumpcooldown;
	}

	if (playerpos.y > 0)
	{
		playerpos.y-=0.2f;
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//DxLib::SetCameraPositionAndAngle(VGet(x, y, z), camrotaver, camrota, 0);
	DxLib::SetCameraPositionAndTarget_UpVecY(VGet(campos.x, campos.y, campos.z), VGet(0,0,0));

	static int groundrotax = 0;
	static int rotaframe = 0;
	rotaframe++;
		//groundrotax+=2.0f; 

		MV1SetPosition(ground_model, VGet(0, 0, 0));
		MV1SetRotationXYZ(ground_model, VGet(TO_RADIAN(groundrotax), TO_RADIAN(0), TO_RADIAN(0)));
		MV1DrawModel(ground_model);

		MV1SetPosition(npc_model, VGet(enemypos.x, enemypos.y, enemypos.z));
		MV1SetRotationXYZ(npc_model, VGet(TO_RADIAN(groundrotax), TO_RADIAN(enemyrota.x), TO_RADIAN(0)));
		MV1DrawModel(npc_model);

		MV1SetPosition(player_model, VGet(playerpos.x, playerpos.y, playerpos.z));
		MV1SetRotationXYZ(player_model, VGet(TO_RADIAN(groundrotax), TO_RADIAN(0), TO_RADIAN(0)));
		MV1DrawModel(player_model);

	DrawSphere3D( VGet( 0.0f, 0, 0.0f ), 2.2f, 100, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );
	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}
