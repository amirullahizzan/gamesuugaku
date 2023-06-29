#include "Main.h"
#include "Game.h"

//	プレイヤー用の変数
int player_image;	//	画像
int player_x;		//	Ｘ座標
int player_y;		//	Ｙ座標
//	ＮＰＣ
int npc_image;
int npc_x[11];
int npc_y[11];
//	アイテム
int item_image;
int item_x;
int item_y;

//---------------------------------------------------------------------------------
//	点と四角の当たり判定をする関数
//		point_x	：渡された点のＸ座標
//		point_y	：　　　　　　Ｙ座標
//		box_x	：渡された四角のＸ座標
//		box_y	：　　　　　　　Ｙ座標
//		box_w	：　　　　　　　横幅
//		box_h	：　　　　　　　高さ
//	０：当たっていない　１：当たっている
//---------------------------------------------------------------------------------
int CheckPointBoxHit( int point_x, int point_y, int box_x, int box_y, int box_w, int box_h )
{
	//	点のＸ座標が四角の左と右の間
	if( point_x >= box_x && point_x <= box_x + box_w ){
		//	点のＹ座標が四角の上と下の間
		if( point_y >= box_y && point_y <= box_y + box_h ){
			//	関数の結果として当たっているので１を返します
			return 1;
		}
	}
	//	当たっていないので０を返します
	return 0;
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込みと初期座標の設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 300;
	player_y = 100;

	for (int i = 0;i<11;i++)
	{
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x[i] = GetRand(SCREEN_W)+200;
	npc_y[i] = GetRand(SCREEN_H);
	}

	item_image = LoadGraph( "data/item.bmp" );
	item_x = 500;
	item_y = 300;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	画面左に移動
	player_x -= 1;
	//	画面の左まで行ったら
	if( player_x < -50 ){
		//	右から出てくる
		player_x = 800;
		//	Ｙ座標はランダムに
		player_y = GetRand( 400 );
	}

	for(int i = 0; i < 11; i++)
	{
	npc_x[i] -= 2;
	if( npc_x[i] < -50 ){
		npc_x[i] = 800;
		npc_y[i] = GetRand( 400 );
	}
	}

	item_x -= 3;
	if( item_x < -50 ){
		item_x = 800;
		item_y = GetRand( 400 );
	}

	//	マウスをクリックしたとき
	if( PushMouseInput() ){
		//	マウス座標を取得
		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();

		//	マウスとプレイヤーの当たり判定
		int check = CheckPointBoxHit( mouse_x, mouse_y, player_x, player_y, 50, 50 );
		//	当たっていたらプレイヤーを画面右にしたい
		if( check == 1 ){
			player_x = 800;
			player_y = GetRand( 400 );
		}

	
		for (int i = 0; i < 11; i++)
		{
		//	マウスとＮＰＣで当たり判定
		if( CheckPointBoxHit( mouse_x, mouse_y, npc_x[i], npc_y[i], 50, 50) == 1) {
			//	当たっていたらＮＰＣを右に
			npc_x[i] = 800;
			npc_y[i] = GetRand( SCREEN_H ) - 50;
		}
		}

		//	マウスとアイテムの当たり判定
		if( CheckPointBoxHit( mouse_x, mouse_y, item_x, item_y, 50, 50 ) ){
			//	当たっていたらアイテムを画面右に
			item_x = GetRand(SCREEN_W) + SCREEN_W;
			item_y = GetRand( 400 );
			for (int i = 0; i < 11; i++)
			{
				npc_x[i] = SCREEN_W + GetRand(SCREEN_W);
				npc_y[i] = GetRand(SCREEN_H)-50;
			}

		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	それぞれの座標にそれぞれの画像を描画
	DrawGraph( item_x, item_y, item_image, TRUE );

	for (int i = 0; i < 11; i++)
	{
	DrawGraph( npc_x[i], npc_y[i], npc_image, TRUE );
	}

	DrawGraph( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "プレイヤー・ＮＰＣ・アイテムをマウスでクリック", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "ＮＰＣを複数に", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "アイテムをクリックしたらＮＰＣ全員やっつけた感じに", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( item_image );
}
