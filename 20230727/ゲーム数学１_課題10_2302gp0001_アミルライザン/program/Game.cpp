#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	移動スピード
#define PLAYER_SPEED	 3.0f	//	プレイヤー
#define NPC_SPEED		 3.0f	//	ＮＰＣ
#define MISSILE_SPEED	10.0f	//	ミサイル

//	大きさ
#define NPC_SIZE		50.0f	//	ＮＰＣ
#define MISSILE_SIZE	20.0f	//	ミサイル

//	プレイヤー用の変数
int player_image;	//	画像
float player_x;		//	Ｘ座標
float player_y;		//	Ｙ座標

//	ＮＰＣ
int npc_image;
float npc_x;
float npc_y;

//	ミサイル
int missile_image;
//	ミサイルの数
#define MISSILE_MAX	100
//	座標
float missile_x[MISSILE_MAX];
float missile_y[MISSILE_MAX];
//	今ミサイルがどんな状態なのか（０：飛んでいない　１：飛んでいる）
int missile_mode[MISSILE_MAX];

int timerms;
						
int icon_image;

int icon_x[MISSILE_MAX];

int killcount;


void GameInit()
{
	//	画像の読み込みと初期座標の設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 700.0f;
	npc_y = 300.0f;
	//	ミサイル画像の読み込み
	missile_image = LoadGraph( "data/missile.bmp" );
	icon_image = LoadGraph("data/icon.bmp");

	killcount = 0;


	//	全ミサイルの初期化
	for( int i = 0; i < MISSILE_MAX; i++ )
	{
		icon_x[i] = -60;
		//	ミサイル座標の初期設定（とりあえず）
		missile_x[i] = 0.0f;
		missile_y[i] = 0.0f;
		//	ミサイルは飛んでいない状態から開始
		missile_mode[i] = 0;
	}
	timerms = 0;
	

}


void AddKillCount()
{
		icon_x[killcount] = 20*killcount;
		killcount++;
}

bool CanBoostTime()
{
	return killcount >= 3;
}

int attackdelay = 10;
const int constboostduration = 200;
int boostduration = 200;

bool isBoostTime = false;


bool isBoostKeepTrack = false;

void BoostReset()
{
	if (isBoostTime)
	{
		boostduration--;
		if (boostduration <= 0 && isBoostTime)
		{
			//reset
			attackdelay = 10;
			boostduration = constboostduration;
			isBoostTime = false;
		}
	}
}

void ActivateBoost()
{
	killcount = 0;
	isBoostTime = true;

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		icon_x[i] = -100;
	}
	attackdelay = 2;
	isBoostKeepTrack = true;
	
}



void GameUpdate()
{
	//	十字キーでプレイヤーの座標移動
	timerms++;

	if(timerms >= attackdelay)
	{
		for (int i = 0; i < MISSILE_MAX; i++) 
		{
			//	ミサイルが飛んでいない状態の時
			if (missile_mode[i] == 0) {
				//	ミサイルを飛ぶ状態に変更
				missile_mode[i] = 1;
				//	ループを抜ける
				break;
			}

		}
		timerms = 0;

	}

	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	
	if (CheckHitKey(KEY_INPUT_SPACE) && CanBoostTime())
	{
		ActivateBoost();
	}

	BoostReset();
	//	スペースキーで
		//	全てのミサイルを見ていって飛んでいないものを見つけたらそれを飛ばす状態にして「ループを終わらせる」
		

	//	全ミサイルの移動処理
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	ミサイルが飛んでないとき
		if( missile_mode[i] == 0 ){
		
			missile_x[i] = player_x + 15.0f;	//	15.0f = 25.0f - 10.0f
			missile_y[i] = player_y + 15.0f;
		}
		//	ミサイルが飛んでいるとき
		if( missile_mode[i] == 1 ){
			//	画面右に移動させる
			missile_x[i] += MISSILE_SPEED;
			//	画面の右まで行ったら
			if( missile_x[i] > SCREEN_W ){
				//	ミサイルを飛ばない状態に
				missile_mode[i] = 0;
			}
		}
	}

	//	ＮＰＣは画面左に移動
	npc_x -= NPC_SPEED;
	//	画面の左まで行ったら
	if( npc_x < -NPC_SIZE ){
		//	右から出てくる
		npc_x = SCREEN_W;
	}

	//	全ミサイルとＮＰＣで当たり判定
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	ミサイルが飛んでいっるとき
		if( missile_mode[i] == 1 ){
			//	移動後のミサイルとＮＰＣで当たり判定（四角同士の当たり判定）
			if( CheckBoxHit( missile_x[i], missile_y[i], MISSILE_SIZE, MISSILE_SIZE, npc_x, npc_y, NPC_SIZE, NPC_SIZE ) ){
				//	当たっていたら
				//	ミサイルを飛ばない状態にします
				missile_mode[i] = 0;
				AddKillCount();
				//	ＮＰＣの座標を再設定
				npc_x = SCREEN_W;
				npc_y = (float)GetRand( SCREEN_H - NPC_SIZE );
			}
		}
	}
}

void GameRender()
{
	//	ＮＰＣの描画
	DrawGraphF( npc_x, npc_y, npc_image, TRUE );

	//	ミサイルの描画
	for( int i = 0;i < MISSILE_MAX; i++ ){
		//	飛んでいるミサイルのみ
		if( missile_mode[i] == 1 ){
			DrawGraphF( missile_x[i], missile_y[i], missile_image, TRUE );
		}
	}

	//	プレイヤーの描画
	DrawGraphF( player_x, player_y, player_image, TRUE );

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		DrawGraphF(20 + icon_x[i], 100, icon_image, TRUE);
	}

	DrawString( 20, 20, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "自動で一定間隔でミサイル発射", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "NPCを倒した数分だけアイコンを並べてみる", GetColor( 150, 200, 225 ) );

	if (CanBoostTime())
	{
		DrawString(20, 300, "Press SPACE to Boost!", GetColor(225, 220, 120));

	}
}

void GameExit()
{
	//	読み込んだ画像の終了処理
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( missile_image );
}
