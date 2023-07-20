#include "Main.h"
#include "Game.h"
//	CheckCircleHit の関数を使いたいので、その名前が書いてあるヘッダーファイルをインクルードします
#include "Hit.h"

//	ＮＰＣの数
#define NPC_MAX		10

//	ＮＰＣ円の半径
#define NPC_RADIUS		25.0f
//	ミサイル円の半径
#define MISSILE_RADIUS	10.0f

//	ミサイル座標
float missile_x;
float missile_y;
//	ミサイルがどんな状態か（０：上下移動する　１：右に移動）
int missile_mode;

//	ＮＰＣ座標
float npc_x[NPC_MAX];
float npc_y[NPC_MAX];

float explosion_radius;
float explosion_x;
float explosion_y;
bool isExploding = false;
bool isMissileExist = true;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ミサイル初期座標
	missile_x = 50.0f;
	missile_y = SCREEN_H / 2.0f;
	//	ミサイルは最初は上下移動させる状態から開始
	missile_mode = 0;

	//	ＮＰＣ初期座標
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc_x[i] = (float)GetRand(SCREEN_W) + SCREEN_W;
		npc_y[i] = (float)GetRand(SCREEN_H - NPC_RADIUS)+NPC_RADIUS;
	}

	explosion_x = 0;
	explosion_y = 0;
	explosion_radius = 0;
}

void ResetNpc(int i)
{
		npc_x[i] = (float)GetRand(SCREEN_W + NPC_RADIUS)+SCREEN_W;
		npc_y[i] = (float)GetRand(SCREEN_H-NPC_RADIUS)+ NPC_RADIUS;
}

void MoveExplosion(int x, int y)
{
	explosion_x = x;
	explosion_y = y;
}

void ResetExplosion()
{
	explosion_x = 0;
	explosion_y = 0;
	explosion_radius = 0;
	isExploding = false;
}


void DestroyMissile()
{
		
		isMissileExist = false;
}

int score = 0;

void ResetMissile()
{
	missile_x = 50.0f;
	missile_y = SCREEN_H / 2.0f;
	missile_mode = 0;
	isMissileExist = true;
}

void SpawnExplosion()
{
	explosion_radius+=6;
	
	for (int i = 0; i < NPC_MAX; i++)
	{
		if (CheckCircleHit(explosion_x, explosion_y, explosion_radius, npc_x[i], npc_y[i], NPC_RADIUS))
		{
			ResetNpc(i);
			score++;
		}
	}
	
	if (explosion_radius >= 200.0f)
	{
		ResetExplosion();
		ResetMissile();
	}
}


void GameUpdate()
{
	//	上下移動をさせる状態の時
	if( missile_mode == 0 ){
		//	上下キーで上下の座標移動
		if( CheckHitKey( KEY_INPUT_DOWN ) )		missile_y += 3.0f;
		if( CheckHitKey( KEY_INPUT_UP ) )		missile_y -= 3.0f;
		//	スペースキーを押したら
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	右に移動させる状態にしたいので
			missile_mode = 1;
		}
	}
	//	飛んでいる状態の時
	if( missile_mode == 1 ){
		//	画面右に移動
		missile_x += 10.0f;
		//	画面の右まで行ったら
		if( missile_x > SCREEN_W + MISSILE_RADIUS ){
			//	上下キーで移動する状態に戻します
			missile_mode = 0;
			//	座標も初期座標に戻します
			missile_x = 50.0f;
			missile_y = SCREEN_H / 2.0f;
		}
	}

	//	画面左に移動
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc_x[i] -= 3.0f;
		//	画面左まで行ったら（円が全部隠れるまで）
		if (npc_x[i] < -NPC_RADIUS)
		{
			ResetNpc(i);
		}
	}

	for (int i = 0; i < NPC_MAX; i++)
	{
		bool check = CheckCircleHit(missile_x, missile_y, MISSILE_RADIUS, npc_x[i], npc_y[i], NPC_RADIUS);
	

	if( check == true && isExploding == false){
		//	ＮＰＣの座標を再設定
		MoveExplosion(missile_x, missile_y);
		isExploding = true;
		
			npc_x[i] = SCREEN_W + NPC_RADIUS;
			npc_y[i] = (float)GetRand(SCREEN_H);

		//	ミサイルを上下移動をする状態に戻します
			DestroyMissile();
	}
	}

	if (isExploding)
	{
		SpawnExplosion();
	}
}



void GameRender()
{
	//	ＮＰＣ座標と半径を渡して円の描画
	DrawCircle(explosion_x, explosion_y, explosion_radius, GetColor(150,255,120) ,0,1 );

	for (int i = 0; i < NPC_MAX; i++)
	{
		DrawCircle(npc_x[i], npc_y[i], NPC_RADIUS, GetColor(255, 128, 128));
	}
	//	ミサイルも
	if (isMissileExist)
	{
		DrawCircle(missile_x, missile_y, MISSILE_RADIUS, GetColor(128, 255, 128));
	}

	DrawString( 20,  20, "上下キー：緑色のミサイル円の上下移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "スペース：ミサイル円の横移動開始", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "赤いＮＰＣ円とミサイル円が当たるとＮＰＣは座標再設定", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "ＮＰＣを複数にする", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "ミサイルがＮＰＣと当たったらミサイルはその場所で広がっていく", GetColor( 255, 255, 0 ) );
	DrawString( 20, 120, "→　広がっているときのミサイル円の描画は枠だけにする", GetColor( 255, 255, 0 ) );
	DrawString( 20, 140, "→　ある程度大きくなったら開始位置に戻る", GetColor( 255, 255, 0 ) );
	DrawFormatString( 20, 300, GetColor(255, 255, 0) , "Enemy Destroyed : %02d ",  score);

}


void GameExit()
{
}
