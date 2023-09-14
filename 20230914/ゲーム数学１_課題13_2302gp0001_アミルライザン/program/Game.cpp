#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	5.0f
//	プレイヤーの回転スピード（度）
#define PLAYER_ROT_SPEED	3.0f
//	ミサイルの移動スピード
#define MISSILE_SPEED		10.0f

//	プレイヤー用の変数
int player_image;		//	画像
float player_x;			//	Ｘ座標
float player_y;			//	Ｙ座標
float player_rot;		//	向き（度）

//	ミサイルの数
#define MISSILE_MAX		300

//	ミサイル用の変数
int missile_image;		//	画像（同じものを使いまわそうと思うので配列にはしていないです）
float missile_x[MISSILE_MAX];		//	Ｘ座標
float missile_y[MISSILE_MAX];		//	Ｙ座標
float missile_rot[MISSILE_MAX];		//	向き（度）
//	ミサイルのモード
enum {
	MODE_WAIT,	//	０：飛んでいない
	MODE_MOVE,	//	１：飛んでいる
};
int missile_mode[MISSILE_MAX];		//	ミサイルが何モードか（０：飛んでいない　１：飛んでいる）

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込みと初期設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;
	player_rot = 0.0f;

	//	ミサイル画像の読み込み
	missile_image = LoadGraph( "data/missile.bmp" );
	//	ミサイルの数分初期化
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	とりあえず（ 100 100 ）にしていますが、最終的には見えない状態から始まります
		missile_x[i] = 100.0f;
		missile_y[i] = 100.0f;
		//	向きも０度にしていますが、撃ったらプレイヤーの向きになる
		missile_rot[i] = 0.0f;
		//	最初は飛んでいない状態から開始
		missile_mode[i] = MODE_WAIT;
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int rotatingmissile = 0;
void GameUpdate()
{
	//	左右キーでプレイヤーの向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_rot += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_rot -= PLAYER_ROT_SPEED;

	//	上キーで向いている方向に移動
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	Ｘ方向にこれだけ進む（長さ PLAYER_MOV_SPEED を player_rot 回転させたときの角度に沿っているほうの長さ）
		float mov_x = PLAYER_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		//	Ｙ方向にこれだけ進む（長さ PLAYER_MOV_SPEED を player_rot 回転させたときの角度の向かいにあるほうの長さ）
		float mov_y = PLAYER_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
		//	この移動させたい分だけ座標に足す
		player_x += mov_x;
		player_y += mov_y;
	}

	//	スペースキーを押したらミサイル発射
	if( PushHitKey( KEY_INPUT_SPACE ) ){
		//	ミサイルを１発だけ撃つ処理
		for( int i = 0; i < MISSILE_MAX; i++ ){
			//	ミサイルが飛んでいないときだけ
			if( missile_mode[i] == MODE_WAIT ){
				//	ミサイルを飛ぶ状態に変更
				missile_mode[i] = MODE_MOVE;
				//	ミサイルの座標をプレイヤーに合わせます
				missile_x[i] = player_x;
				missile_y[i] = player_y;
				//	ミサイルの向きをプレイヤーに合わせます
				missile_rot[i] = player_rot;

				//	スペースキーを押してミサイルを撃つのは１発だけにしたいのでループを終わらせます
				break;
			}
		}
	}

	if( PushHitKey( KEY_INPUT_1 ) ){
		for (int j = 0; j < 3; j++)
		{
		for( int i = 0; i < MISSILE_MAX; i++ ){
			if( missile_mode[i] == MODE_WAIT )
			{
				missile_mode[i] = MODE_MOVE;
				missile_x[i] = player_x;
				missile_y[i] = player_y;
				missile_rot[i] = player_rot + j * 20.0f - 20.0f;
				break;
			}
		}
		}
	}

	if( PushHitKey( KEY_INPUT_2 ) )
	{
		for (int j = 0; j < 36; j++)
		{
			for (int i = 0; i < MISSILE_MAX; i++)
			{
				if (missile_mode[i] == MODE_WAIT)
				{
					missile_mode[i] = MODE_MOVE;
					missile_x[i] = player_x;
					missile_y[i] = player_y;
					missile_rot[i] = player_rot + (10 * j);
					break;
				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_3)) 
	{
		if (rotatingmissile >= 36)
		{
			rotatingmissile = 0;
		}
		rotatingmissile++;
			for (int i = 0; i < MISSILE_MAX; i++)
			{
				if (missile_mode[i] == MODE_WAIT)
				{
					missile_mode[i] = MODE_MOVE;
					missile_x[i] = player_x;
					missile_y[i] = player_y;
					missile_rot[i] = player_rot + (10 * rotatingmissile);
					break;
				}
			}
	}


	//	ミサイルの移動処理
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	ミサイルが飛んでいるときのみ移動する
		if( missile_mode[i] == MODE_MOVE ){
			//	ミサイルがＸ方向にこれだけ進む
			float mov_x = MISSILE_SPEED * GetLength_RotSotte( TO_RADIAN( missile_rot[i] ) );
			//	Ｙ方向も
			float mov_y = MISSILE_SPEED * GetLength_RotMukai( TO_RADIAN( missile_rot[i] ) );
			//	この分だけ座標移動
			missile_x[i] += mov_x;
			missile_y[i] += mov_y;

			//	画面の外に出たら飛ばない状態にします
			if( missile_x[i] <     0.0f )	missile_mode[i] = MODE_WAIT;
			if( missile_x[i] > SCREEN_W )	missile_mode[i] = MODE_WAIT;
			if( missile_y[i] <     0.0f )	missile_mode[i] = MODE_WAIT;
			if( missile_y[i] > SCREEN_H )	missile_mode[i] = MODE_WAIT;
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	ミサイルが飛んでいるときだけ
		if( missile_mode[i] == MODE_MOVE ){
			//	ミサイルを描画します
			DrawRotaGraphF( missile_x[i], missile_y[i], 1.0f, TO_RADIAN( missile_rot[i] ), missile_image, TRUE );
		}
	}

	//	プレイヤーの座標と向きを渡してプレイヤー画像の描画
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20,  20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "スペース：ミサイル発射", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "１キー　：３方向ミサイル", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "２キー　：３６０度ミサイル", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( missile_image );
}
