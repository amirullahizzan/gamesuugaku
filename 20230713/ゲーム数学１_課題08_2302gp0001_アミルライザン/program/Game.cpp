#include "Main.h"
#include "Game.h"

//	円の最大数
#define CIRCLE_MAX	5

//	円の半径（今回は半径の大きさは変わらないので）
#define RADIUS		50.0f
//	円のＸ座標
float pos_x[CIRCLE_MAX];
//	円のＹ座標
float pos_y[CIRCLE_MAX];
//	円をクリックしたかどうかの変数（０：クリックしていない　１：クリックした）
int click[CIRCLE_MAX];

//	円の座標とマウス座標の距離を入れる用の変数
float distance[CIRCLE_MAX];

//---------------------------------------------------------------------------------
//	２点の距離を返す関数
//		x1 y1：１点目の座標
//		x2 y2：２点目の座標
//	２点の距離を返します（ float 型の値です）
//---------------------------------------------------------------------------------
float GetDistance( float x1, float y1, float x2, float y2 )
{
	//	Ｘ方向の差
	float x = x1 - x2;
	//	Ｙ方向の差
	float y = y1 - y2;
	//	上で求めたＸ方向とＹ方向の差から２点間の距離を求める
	//	sqrtf：受け取った値をルートする関数
	float d = sqrtf( x * x + y * y );
	//	その距離を返す
	return d;
}
int speed[CIRCLE_MAX];
int color[CIRCLE_MAX];


bool Done[5];

void GameInit()
{
	//	とりあえず円の初期座標（画面の上から開始）
	for (int i = 0;i< CIRCLE_MAX;i++)
	{
		pos_x[i] = 100 + (100 * i) ;
		pos_y[i] = -RADIUS;
		speed[i] = GetRand(20);
		color[i] = GetColor(128, 128, 128);
		Done[i] = false;
		click[i] = 0;
	}
	
	//	クリックしていない状態から開始
}

void GameUpdate()
{
	//	円の移動
	int ballOutCount = 0;

	float mouse_x = (float)GetMouseX();
	float mouse_y = (float)GetMouseY();

	for (int i = 0;i< CIRCLE_MAX;i++)
	{

		pos_y[i] += (speed[i]/10.0f)+1.0f;
		if (pos_y[i] > SCREEN_H + RADIUS) 
		{
			//	画面の上から（円がすべて隠れている状態から開始したい）
			//	画面の上から出てくるタイミングでクリック状態を解除する
			ballOutCount++;

			
			
		}

	
			distance[i] = GetDistance(pos_x[i], pos_y[i], mouse_x, mouse_y);

			if (PushMouseInput()) 
			{
				//	円の中にマウス座標が入っていたら（２点の距離と半径の比較）
				if (distance[i] <= RADIUS) {
					//	円をクリックできたので
					click[i] = 1;
				}
			}

	}

	if (ballOutCount == CIRCLE_MAX)
	{
		for (int i = 0; i < CIRCLE_MAX; i++)
		{
			pos_y[i] = -RADIUS;
			click[i] = 0;
			speed[i] = (float)GetRand(20);
			color[i] = GetColor(128, 128, 128);
		}

	}

}


void GameRender()
{
	//	灰色で（クリックしたら色を変えようと思います）
	//	クリックされているのであれば
	
	//	その色で円の描画

	for (int i = 0;i< CIRCLE_MAX;i++)
	{
		DrawCircle(pos_x[i], pos_y[i], RADIUS, color[i]);
		if (click[i] == 1)
		{
			//	色を変更する
			color[i] = GetColor(128, 128, 255);
		}
	}

	DrawString( 20,  20, "マウスで円をクリック", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "→　クリックされたら色の変更", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "→　画面下まで行ったら色を戻して画面の上に", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "円を複数にして並べる", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "円は 1.0 ～ 3.0 のランダムなスピードで画面下に移動", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}
