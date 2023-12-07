#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理

//	ステージの範囲
#define STAGE_X_MIN	-20.0f	//	Ｘ座標ここから
#define STAGE_X_MAX	 20.0f	//	Ｘ座標ここまで
#define STAGE_Z_MIN	-10.0f	//	Ｚ座標ここから
#define STAGE_Z_MAX	 30.0f	//	Ｚ座標ここまで

//	緑のエリアの範囲
#define AREA_X_MIN	 5.0f	//	Ｘ座標ここから
#define AREA_X_MAX	15.0f	//	Ｘ座標ここまで
#define AREA_Z_MIN	 5.0f	//	Ｚ座標ここから
#define AREA_Z_MAX	15.0f	//	Ｚ座標ここまで
