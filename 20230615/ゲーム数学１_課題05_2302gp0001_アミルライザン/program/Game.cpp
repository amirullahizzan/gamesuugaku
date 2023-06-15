#include "Main.h"
#include "Game.h"

//	プレイヤーの移動スピード
#define PLAYER_SPEED	5
//	ＮＰＣのスピード
#define NPC_SPEED		3

//	プレイヤー画像
int player_image;
//	プレイヤー座標
int player_x;
int player_y;

//	ＮＰＣ画像
int npc_image;
//	ＮＰＣ座標
int npc_x;
int npc_y;

//	「当たりました」を表示させるためのカウンター
int draw_frame;

//	空画像用の変数
int sky_image;
//	地面画像用の変数
int ground_image;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	空画像・地面画像の読み込み
	sky_image = LoadGraph( "data/sky.bmp" );
	ground_image = LoadGraph( "data/ground.bmp" );

	//	画像の読み込みと初期座標の設定
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100;
	player_y = 200;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 300;
	npc_y = 300;

	draw_frame = 0;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int skymover = 0;
int groundmover = 0;


bool isPlayerStunned = false;
void GameUpdate()
{
	//	十字キーを押したらプレイヤー座標の更新
	if (!isPlayerStunned)
	{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	}

	if (player_x < 0)
	{
		player_x = 0;
	}
	if (player_x > SCREEN_W-50)
	{
		player_x = SCREEN_W-50;
	}
	if (player_y < 0)
	{
		player_y = 0;
	}
	if (player_y > SCREEN_H-50)
	{
		player_y = SCREEN_H-50;
	}

	//	ＮＰＣの座標移動
	//	画面左に移動
	npc_x -= NPC_SPEED;
	//	画面の左に行ったら
	if( npc_x < -50 ){
		//	右に戻す
		npc_x = 800;
		//	Ｙ座標はランダムに
		npc_y = GetRand( 400 );
	}

	//	プレイヤーとＮＰＣで当たり判定（四角同士の当たり判定）
	if( player_x <= npc_x + 50 && player_x + 50 >= npc_x ){
		if( player_y <= npc_y + 50 && player_y + 50 >= npc_y ){
			//	当たっていたらＮＰＣの座標を再設定
			npc_x = 800;
			//	Ｙ座標をランダムに
			npc_y = GetRand( 400 );

			//	表示時間のセット（１秒：６０フレームなので）
			draw_frame = 60;

			isPlayerStunned = true;
			
		}
	}

	

	//	文字列表示カウンターの値を減らしていく
	draw_frame--;
	if( draw_frame < 0 ){
		draw_frame = 0;
		isPlayerStunned = false;
	}

	
	skymover+= 2;

	if (skymover > 800)
	{
		skymover = 0;
	}

	groundmover += 4;

	if (groundmover > 800)
	{
		groundmover = 0;
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	とりあえず画面左上に表示だけしています（課題の実装をするのでこれはコメントにします）
	DrawGraph(0-skymover, 0, sky_image, TRUE);
	DrawGraph( SCREEN_W-skymover, 0, sky_image, TRUE );

	DrawGraph( 0- groundmover, 400, ground_image, TRUE );
	DrawGraph(400 - groundmover, 400, ground_image, TRUE);
	DrawGraph(400 + 400 - groundmover, 400, ground_image, TRUE);
	DrawGraph(800+400- groundmover, 400, ground_image, TRUE);


	//	ＮＰＣの描画
	DrawGraph( npc_x, npc_y, npc_image, TRUE );
	//	プレイヤーの描画
	DrawGraph( player_x, player_y, player_image, TRUE );

	//	当たった後カウンターの中に値が入っている１秒間だけ
	if( draw_frame > 0 ){
		DrawString( 20, 150, "当たりました", GetColor( 255, 255, 0 ) );
	}

	DrawString( 20, 20, "十字キー：プレイヤー移動（画面外に行かない（地面より下にもいかない）", GetColor( 255, 255, 0 ) );
	DrawString( 20, 40, "ＮＰＣも地面より下にはいかない", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "プレイヤーとＮＰＣが当たるとＮＰＣの座標再設定", GetColor( 255, 255, 255 ) );
	DrawString( 20, 80, "「当たりました」表示中プレイヤーは移動ができない", GetColor( 255, 255, 0 ) );

	DrawString( 20, 100, "背景表示とスクロール　(空：ゆっくり　地面：少し速い)", GetColor( 40, 200, 240 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( sky_image );
	DeleteGraph( ground_image );
}
