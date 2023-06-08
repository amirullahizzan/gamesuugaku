#include "Main.h"
#include "Game.h"

//	ＮＰＣの画像用の変数
int npc_image;
//	ＮＰＣの座標用の変数



int npc_x[5];	//	Ｘ座標
int npc_y[5];	//	Ｙ座標

//	ＮＰＣをクリックした回数を入れておく用の変数
int click_count;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	ＮＰＣ画像の読み込み
	npc_image = LoadGraph( "data/npc.bmp" );
	//	初期座標の設定

	//	クリック回数０から開始
	click_count = 0;

	for (int i = 0; i < 5; i++)
	{
		npc_x[i] = 100 + GetRand(500);
		npc_y[i] = GetRand(SCREEN_H - 50);
	}
}



void GameUpdate()
{
	int mouse_x = GetMouseX();
	int mouse_y = GetMouseY();
	//	マウスをクリックしたとき

	for (int i = 0;i<5;i++)
	{
		npc_x[i] -= 2;


		if(npc_x[i] < 0)
		{
		npc_x[i] = SCREEN_W + 50;
		}

		if( PushMouseInput() )
		{
		//	マウス座標の取得
	
		

		//	ここで取得したマウス座標（点）とＮＰＣ（四角）で判定をします
			if( mouse_x >= npc_x[i] && mouse_x <= npc_x[i] + 50 )
			{
			//	縦方向の判定
				if( mouse_y >= npc_y[i] && mouse_y <= npc_y[i] + 50 )
				{
				//	当たっていたらＮＰＣの座標をランダムで設定
				npc_x[i] = SCREEN_W + GetRand(500);
				npc_y[i] = GetRand( SCREEN_H - 50 );

				//	ＮＰＣがクリックできたのでクリック回数を増やします
				i--;
				click_count++;
				}
			}

		}



	}
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	読み込んだＮＰＣ画像を座標変数の場所に描画
	for (int j = 0; j < 5;j++)
	{

		DrawGraph(npc_x[j], npc_y[j], npc_image, TRUE);

	}

	//	クリック数の文字列をＮＰＣよりも手前に表示したいのでＮＰＣ描画の後に記述します
	DrawFormatString( 20, 80, GetColor( 255, 255, 255 ), "ＮＰＣクリック数：%d", click_count );

	DrawString( 20, 20, "ＮＰＣ画面左に移動（左まで行ったら右から出てくる）", GetColor( 255, 255, 0 ) );
	DrawString( 20, 40, "ＮＰＣクリック：再び画面右から出てくる", GetColor( 255, 255, 0 ) );

	DrawString( 20, 60, "ＮＰＣが画面左に行ったらクリック数リセット", GetColor( 255, 255, 0 ) );
	
	DrawString( 20, 100, "ＮＰＣを複数表示", GetColor( 80, 210, 240 ) );
}


void GameExit()
{
	//	読み込んだＮＰＣ画像の終了処理
	DeleteGraph( npc_image );
}
