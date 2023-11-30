#include "Main.h"
#include "Game.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

Ground ground;
Player player;
Camera camera;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground.Init();
	player.Init();
	camera.Init();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	player.Update();
	camera.Update(player.m_pos);
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("angle : %f", player.m_rot.y);

	camera.Render();
	ground.Render();
	player.Render();

	DrawString( 16, 16, "クラスで実装", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "十字キー：プレイヤー移動（向きを変えて）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "スペース：ジャンプ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "Ｆ１キー：ステージ全体を見るカメラ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "Ｆ２キー：プレイヤーを見るカメラ", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	ground.Exit();
	player.Exit();
	camera.Exit();
}
