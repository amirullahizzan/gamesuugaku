#include "Main.h"
#include "Game.h"

//	円を左右に移動させたいのでＸ座標用の変数
int pos_x[10];
int pos_y[10];


//	Ｘ方向の移動量を入れる用の変数
int mov_x[10];
int mov_y[10];

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	とりあえず横方向は真ん中にしとくので４００
	for (int i = 0; i < 10; i++)
	{
		pos_x[i] = GetRand(SCREEN_W);
		pos_y[i] = GetRand(SCREEN_H);
	}
	//	右移動から開始したいので
	for(int i = 0; i < 10; i++)
	{
	mov_x[i] = 5;
	mov_y[i] = 5;
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	Ｘ方向の移動量（ mov_x ）をＸ座標（ pos_x ）に足す
	for (int i = 0; i < 10; i++)
	{
		pos_x[i] += mov_x[i];
		pos_y[i] += mov_y[i];
	}

	
	for (int i = 0; i < 10; i++)
	{
		
	
	//	円のＸ座標が「右を超えた」もしくは「左を超えた」のであれば
	if (pos_x[i] > 800 || pos_x[i] < 0) {
		//	移動量の符号を逆にします（プラスだったらマイナスに、マイナスだったらプラスに）
		mov_x[i] *= -1;
	}
	if (pos_y[i] > SCREEN_H || pos_y[i] < 0) {
		//	移動量の符号を逆にします（プラスだったらマイナスに、マイナスだったらプラスに）
		mov_y[i] *= -1;
	}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	Ｘ座標の変数の値を使って円の描画
	for (int i = 0; i < 10; i++)
	{
		DrawCircle(pos_x[i], pos_y[i], 10, GetColor(255, 255, 0));
	}

	DrawString(20, 20, "円が上下左右に跳ね返るように移動", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}
