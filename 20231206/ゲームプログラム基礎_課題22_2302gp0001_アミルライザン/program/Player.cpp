#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Player.h"

//	プレイヤーの加速度
#define PLAYER_ADD_SPEED	0.2f
//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	5.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	m_image = image;
	//	初期座標の設定（ゲーム内座標）
	m_pos.set( 200.0f, 300.0f );
	//	移動量は最初は０で開始
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	移動量を増やしたり減らしたり
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){		//	右を押しているとき
		//	移動量を増やしていく
		m_mov.x += PLAYER_ADD_SPEED;
		if( m_mov.x > PLAYER_MOV_SPEED ){
			m_mov.x = PLAYER_MOV_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){	//	左を押しているとき
		//	移動量を減らしていく
		m_mov.x -= PLAYER_ADD_SPEED;
		if( m_mov.x < -PLAYER_MOV_SPEED ){
			m_mov.x = -PLAYER_MOV_SPEED;
		}
	}else{	//	どちらも押していない時
		//	移動量を０にしていく
		if( m_mov.x > 0.0f ){
			m_mov.x -= PLAYER_ADD_SPEED;
			if( m_mov.x < 0.0f ){
				m_mov.x = 0.0f;
			}
		}
		if( m_mov.x < 0.0f ){
			m_mov.x += PLAYER_ADD_SPEED;
			if( m_mov.x > 0.0f ){
				m_mov.x = 0.0f;
			}
		}
	}
	static bool iscanJump = true;
	static int jumptimer = 300;

	//	スペースキーを押したらジャンプ開始
	if( PushHitKey( KEY_INPUT_SPACE ) && iscanJump){
		//	ジャンプ力設定
		m_mov.y = -10.0f;
		jumptimer = (60);
		iscanJump = false;
	}
		
	if (!iscanJump)
	{
		jumptimer--;
		if (jumptimer < 0)
		{
			iscanJump = true;
		}
	}

	//	移動量分座標移動
	m_pos += m_mov;

	//	Ｙ方向の移動量を毎フレーム少しずつ増やす
	m_mov.y += 0.3f;

	//	地面の高さ（ 300.0f ）よりは下に行かないように
	if( m_pos.y > 300.0f ){
		m_pos.y = 300.0f;
		m_mov.y = 0.0f;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
//void Player::Render()
//{
//	DrawGraphF( m_pos.x, m_pos.y, m_image, TRUE );
//}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
