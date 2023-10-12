#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"		//	hit.h の中で Float2.h インクルードしているけどここでもインクルードしときます

//	プレイヤーとＮＰＣの半径
#define CHARA_RADIUS	25.0f

//	プレイヤー用の変数
int player_image;		//	画像
Float2 player_pos;		//	座標（Ｘ座標とＹ座標の２つの float がある構造体）
float player_rot;		//	向き（度）
//	プレイヤーの移動量
Float2 player_mov;

//	ＮＰＣ用の変数
int npc_image;
Float2 npc_pos;
float npc_rot;

//	マウス座標を入れる用の変数（更新処理と描画処理でマウス座標の値を使うので）
Float2 mouse;

//	マウスドラッグ中かどうか
bool mouse_drag;

Float2 point_pos;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	初期座標や向きの設定
	//	とりあえず画面中央に表示しときます
	player_pos.x = SCREEN_W / 2;
	player_pos.y = SCREEN_H / 2;
	player_rot = 0.0f;

	npc_pos.x = GetRand( SCREEN_W );
	npc_pos.y = GetRand( SCREEN_H );
	npc_rot = 0.0f;
}

float drag_x;
float drag_y;

void GameUpdate()
{
	//	マウス座標の取得
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	マウスを押した瞬間
	if( PushMouseInput() ){
		//	１：マウスのところにプレイヤーを置く
		point_pos.x = mouse.x;
		point_pos.y = mouse.y;
	}

	//	マウスを押しているとき
	if( CheckMouseInput() ){
		//	マウスを押しているので
		mouse_drag = true;
		player_pos.x = mouse.x;
		player_pos.y = mouse.y;

		//	２：プレイヤーの向きをマウス座標の方に
		//	プレイヤーからマウス座標がどれだけ進んだところにあるか
		drag_x = point_pos.x - player_pos.x;
		drag_y = point_pos.y - player_pos.y;

		//	上で求めたプレイヤーからマウスまでの値を移動量として持っておきます
		//	そのままだと大きすぎるので適当に小さくします（ 0.05 倍します）
		player_mov.x = drag_x * 0.05f;
		player_mov.y = drag_y * 0.05f;

		//	この値を使って角度を求めます
//		float radian = GetRadian_LengthYX( y, x );
		//	同じ割合で短くした player_mov を使っても同じ角度がもらえます
		float radian = GetRadian_LengthYX( player_mov.y, player_mov.x );
		//	プレイヤーの角度変数は「度」なので、ラジアン角を度に変換して渡します
		player_rot = TO_DEGREE( radian ); 

	}else{
		//	押していないので
		mouse_drag = false;

		//	マウスを押しているときに決めた移動量を使ってプレイヤーの座標の更新
		player_pos.x += player_mov.x;
		player_pos.y += player_mov.y;
	}

	//	ＮＰＣの回転
	npc_rot += 1.0f;

	//	プレイヤーとＮＰＣの当たり判定（円同士の当たり判定）
	if( CheckCircleHit( player_pos, CHARA_RADIUS, npc_pos, CHARA_RADIUS ) ){
		//	当たったら座標をランダムに
		npc_pos.x = GetRand( SCREEN_W );
		npc_pos.y = GetRand( SCREEN_H );
	}

	if (player_pos.x > SCREEN_W-CHARA_RADIUS || player_pos.x < 0 + CHARA_RADIUS )
	{
		player_mov.x *= -1;

	

		player_rot = TO_DEGREE(atan2f (player_mov.y, player_mov.x) );
	}
	if (player_pos.y > SCREEN_H - CHARA_RADIUS || player_pos.y < 0 + CHARA_RADIUS)
	{
		player_mov.y *= -1;
		player_rot = TO_DEGREE(atan2f(player_mov.y, player_mov.x));

	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの描画
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );
	//	プレイヤーの描画
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	//	マウスドラッグ中の時
	if( mouse_drag ){
		//	プレイヤー座標とマウス座標を線で結ぶ
		DrawLineAA( point_pos.x, point_pos.y, mouse.x, mouse.y, GetColor( 255, 255, 0 ) );
		//	マウス座標のところに円の描画
		DrawCircleAA( point_pos.x, point_pos.y, 5.0f, 100, GetColor( 255, 255, 0 ) );
	}

	DrawString( 16, 16, "マウスクリック：クリック座標設定", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "マウスドラッグ：マウスの所にプレイヤーを置く（プレイヤーはクリック座標の方を向く）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "→　プレイヤーとクリック座標を結んだ線を描画", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "マウスボタンを離したらプレイヤーは向いている方向に移動する", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "→　線が長いほど移動が速い", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "プレイヤーとＮＰＣで当たり判定", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
