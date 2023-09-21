#include "Main.h"
#include "Game.h"

//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	5.0f
//	プレイヤーの回転スピード（度）
#define PLAYER_ROT_SPEED	3.0f

//	オプションがプレイヤーからどれだけ離れるか
//	近い距離
#define LENGTH_NEAR		50.0f
//	遠い距離
#define LENGTH_FAR		100.0f
//	オプションの数
#define OPTION_MAX		6

//	プレイヤー用の変数
int player_image;	//	画像
float player_x;		//	Ｘ座標
float player_y;		//	Ｙ座標
float player_rot;	//	向き

//	オプション用の変数
int option_image;	//	画像（同じ画像を使いまわそうと思いますのでオプション画像は１個）
float option_x[OPTION_MAX];		//	Ｘ座標
float option_y[OPTION_MAX];		//	Ｙ座標
float option_rot[OPTION_MAX];	//	向き

//	プレイヤーからオプションまでの基準の距離
float base_length;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	option_image = LoadGraph( "data/option.bmp" );
	//	プレイヤーの初期設定
	player_x = 100.0f;
	player_y = 250.0f;
	player_rot = 0.0f;
	//	更新処理ですぐに座標や向きが設定されるのですがとりあえず
	for( int i = 0; i < OPTION_MAX; i++ ){
		option_x[i] = 100.0f + 50.0f * i;
		option_y[i] = 300.0f;
		option_rot[i] = 0.0f;
	}
	//	開始時は近い距離から始める
	base_length = LENGTH_NEAR;
}

float rotator = 0;

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
		//	この長さだけ座標移動
		player_x += mov_x;
		player_y += mov_y;
	}

	//	左シフトキーで距離の変更
	if( CheckHitKey( KEY_INPUT_LSHIFT ) ){
		//	押しているときは遠い距離
		if (base_length <= LENGTH_FAR)
		{
		base_length+=5;
		}
	}else{
		if (base_length >= LENGTH_NEAR)
		{
			//	押していないときは近い距離
			base_length-=5;
		}
	}
	//	プレイヤーの座標と向きの更新が終わりましたので（距離も決まったので）その状態からそれぞれのオプションの座標や向きを決定します
	for( int i = 0; i < OPTION_MAX; i++ ){

		//	プレイヤーの向き（に９０度ずつ足した方向）に base_length 分ずらすためのＸ方向とＹ方向の長さを求めます
		
		rotator+=0.5;
		if (rotator>=360)
		{
			rotator = 0;
		}
		float mov_x = base_length * GetLength_RotSotte( TO_RADIAN( player_rot + 360/OPTION_MAX * i +rotator) );	//	GetLength_RotSotte は cos 関数のことです
		float mov_y = base_length * GetLength_RotMukai( TO_RADIAN( player_rot + 360/ OPTION_MAX * i + rotator) );	//	GetLength_RotMukai は sin 関数のことです

		//	オプション座標はプレイヤー座標から上で求めた分だけ進んだところ
		option_x[i] = player_x + mov_x;
		option_y[i] = player_y + mov_y;

		//	プレイヤーの向きに合わせる
		option_rot[i] = player_rot;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	プレイヤー座標と向きを渡してプレイヤー画像の描画
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	//	オプションの描画
	for( int i = 0; i < OPTION_MAX; i++ ){
		DrawRotaGraphF( option_x[i], option_y[i], 1.0f, TO_RADIAN( option_rot[i] ), option_image, TRUE );
	}

	DrawString( 20,  20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "オプションを増やしてプレイヤーの周りを回転させてみる", GetColor( 255, 255, 0 ) );
	DrawString( 20,  80, "左シフトキー：オプションの距離を遠くに", GetColor( 255, 255, 255 ) );
	DrawString( 20, 100, "→　距離の切り替えをスムーズに", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}
