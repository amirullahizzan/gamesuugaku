#include "Main.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	0.1f
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	左右キーで向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_rot.y += PLAYER_ROT_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_rot.y -= PLAYER_ROT_SPEED;
	}
	//	上キーで向いている方向に移動
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.x += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
		m_pos.z += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
