#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	5.0f
//	プレイヤーの回転スピード（３度のスピードで回転させる）
#define PLAYER_ROT_SPEED	3.0f
//	ＮＰＣの移動スピード
#define NPC_SPEED			1.0f
//	プレイヤーとＮＰＣの半径（同じ大きさの画像なので共通でこの定数を使っています）
#define RADIUS				25.0f

#define MAX_ENEMY 20
//	プレイヤー用の変数
int player_image;		//	画像
float player_x;			//	Ｘ座標
float player_y;			//	Ｙ座標
float player_rot;		//	向き（回転角度：度）

//	ＮＰＣ用の変数
int npc_image;			//	画像
float npc_x[MAX_ENEMY];			//	Ｘ座標
float npc_y[MAX_ENEMY];			//	Ｙ座標
float npc_rot[MAX_ENEMY];			//	向き（度）

void GameInit()
{
	//	画像の読み込み（右向きの画像）
	player_image = LoadGraph( "data/player.bmp" );
	//	初期座標の設定
	player_x = 100.0f;
	player_y = 200.0f;
	//	プレイヤー画像の初期向き（０度から始める）
	player_rot = 0.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		npc_x[i] = 500.0f;
		npc_y[i] = 300.0f;
		//npc_rot[i] = GetRand(360);
		npc_rot[i] = (360.0f/MAX_ENEMY)*i;
	}
	//	ＮＰＣは初期設定でランダムな向きに
}

void GameUpdate()
{
	//	左右キーで回転
	//	右キーを押しているとき
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	画像を右回転させたい（角度的にはプラス方向）
		player_rot += PLAYER_ROT_SPEED;
	}
	//	左キーを押しているとき
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//	画像を左回転させたい（角度的にはマイナス方向）
		player_rot -= PLAYER_ROT_SPEED;
	}

	//	上キーで向いている方向に移動
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	player_rot の方向に PLAYER_MOV_SPEED 分座標移動
		player_x += PLAYER_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		player_y += PLAYER_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
	}

	//	ＮＰＣの座標移動（向いている方向に移動）


	//	画面の外に行ったら反対から出てくる


	//	プレイヤーとＮＰＣで当たり判定
	for (int i = 0 ; i < MAX_ENEMY ;i++)
	{
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x[i], npc_y[i], RADIUS))
	{
		//	当たっていたらＮＰＣの座標と向きをランダムに再設定
		npc_x[i] = GetRand(SCREEN_W - RADIUS) + RADIUS;
		npc_y[i] = GetRand(SCREEN_H - RADIUS) + RADIUS;
		npc_rot[i] = GetRand(360);
	}
	//BOUNDARY
	if (npc_x[i] < 0)
	{
		npc_x[i] = SCREEN_W;
	}
	if (npc_y[i] < 0)
	{
		npc_y[i] = SCREEN_H;
	}
	if (npc_x[i] > SCREEN_W)
	{
		npc_x[i] = 0;
	}
	if (npc_y[i] > SCREEN_H)
	{
		npc_y[i] = 0;
	}

	npc_x[i] += cosf(TO_RADIAN(npc_rot[i])) * NPC_SPEED;
	npc_y[i] += sinf(TO_RADIAN(npc_rot[i])) * NPC_SPEED;
	}

	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの座標と向きを渡して描画
	for (int i = 0 ;i < MAX_ENEMY; i++)
	{
	DrawRotaGraphF( npc_x[i], npc_y[i], 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	//	座標と向きを渡して画像を描画（ player_rot：度をラジアンに変換して関数に渡しています）
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20,  20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "ＮＰＣは初期設定でランダムな向きに", GetColor( 255, 255, 0 ) );
	DrawString( 20,  80, "ＮＰＣも向いている方向に移動", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "ＮＰＣはプレイヤーと当たると座標と向きを再設定", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
