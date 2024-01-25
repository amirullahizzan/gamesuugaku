#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

#define COLOR_WHITE		GetColor( 255, 255, 255 )
#define COLOR_YELLOW	GetColor( 255, 255,   0 )

#define COLOR_PLAYER	GetColor( 128, 128, 255 )
#define COLOR_NPC		GetColor( 255, 128, 128 )

void GameInit();	//	初期化処理
void GameUpdate();	//	更新処理
void GameRender();	//	描画処理
void GameExit();	//	終了処理
