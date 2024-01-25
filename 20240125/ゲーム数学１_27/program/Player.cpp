#include "Main.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	0.1f
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.set( 0.0f, 0.0f, -5.0f );
	m_rot.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Player::Update()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_rot += Float3(0, PLAYER_ROT_SPEED, 0);
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_rot -= Float3(0, PLAYER_ROT_SPEED, 0);
	}

	if( CheckHitKey( KEY_INPUT_UP ) )
	{
		float radianY = TO_RADIAN(m_rot.y);
		m_pos.z += cosf(radianY) * PLAYER_MOV_SPEED;
		m_pos.x += sinf(radianY) * PLAYER_MOV_SPEED;
	}

	if (m_rot.y < -360)
	{
		m_rot.y = 0;
	}
	else if (m_rot.y > 360)
	{
		m_rot.y = 0;
	}

}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Player::Render()
{
	clsDx();
	printfDx(" rot : %f",m_rot.y);
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
