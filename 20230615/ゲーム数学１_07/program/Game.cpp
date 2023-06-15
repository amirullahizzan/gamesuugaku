#include "Main.h"
#include "Game.h"

//定数
#define PLAYER_SPEED 5
#define NPC_SPEED 3

int player_image;
int player_x;
int player_y;

int npc_image;
int npc_x;
int npc_y;

bool isMainMenu;
bool isGame;

void GameInit()
{
	player_image = LoadGraph("data/player.bmp");
	player_x = 100;
	player_y = 200;

	npc_image = LoadGraph("data/npc.bmp");
	npc_x = 300;
	npc_y = 300;

	isMainMenu = true;
	isGame = false;
}

bool isatari = false;

void ResetEnemy()
{
		npc_x = 800;
		npc_y = GetRand(400);
}

int mstick = 0;


void GameUpdate()
{
	if (isMainMenu)
	{
		if (PushHitKey(KEY_INPUT_RETURN))
		{
			isMainMenu = false;
			isGame = true;
		}
	}

	if (isGame)
	{
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			player_x += PLAYER_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			player_x -= PLAYER_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			player_y += PLAYER_SPEED;
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			player_y -= PLAYER_SPEED;
		}

		npc_x -= NPC_SPEED;

		if (npc_x < -50) {
			ResetEnemy();
		}

		if ((player_x + 50 > npc_x && player_x < npc_x + 50) && (player_y + 50 > npc_y && player_y < npc_y + 50))
		{
			isatari = true;
			mstick = 0;
			ResetEnemy();
		}
	}


}


void DisplayAtari()
{
	if (isatari && mstick < 120)
	{
		mstick++;
		DrawString(20, 150, "当たりました", GetColor(255, 255, 0));
		if (mstick > 120-1)
		{
			isatari = false;
			mstick = 0;
		}
	}
}

void GameRender()
{
	if (isMainMenu)
	{
		DrawString(300, 300, "Press Enter to Start", GetColor(255, 255, 255));
	}

	if (isGame)
	{
		DrawGraph(npc_x, npc_y, npc_image, TRUE);

		DrawGraph(player_x, player_y, player_image, TRUE);

		DisplayAtari();

		DrawString(20, 20, "十字キー：プレイヤー移動", GetColor(255, 255, 255));
		DrawString(20, 40, "プレイヤーとＮＰＣが当たるとＮＰＣの座標再設定", GetColor(255, 255, 255));
	}
	
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
