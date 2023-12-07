#include "Main.h"
#include "Game.h"
#include "Player.h"

#define PLAYER_SPEED	0.2f
#define PLAYER_ACCEL	0.005f

//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;
	m_pos.set( 0.0f, 0.0f, 0.0f );
	m_rot.set( 0.0f, 0.0f, 0.0f );
	m_size.set( 0.5f, 0.5f, 0.5f );
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	XVˆ—
//---------------------------------------------------------------------------------
void Player::Update()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_mov.x += PLAYER_ACCEL;
		if (m_mov.x > PLAYER_SPEED)
		{
			m_mov.x = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_mov.x -= PLAYER_ACCEL;
		if (m_mov.x < -PLAYER_SPEED)
		{
			m_mov.x = -PLAYER_SPEED;
		}
	}
	else
	{
		m_mov.x *= 0.95f;
	}

	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_mov.z += PLAYER_ACCEL;
		if (m_mov.z > PLAYER_SPEED)
		{
			m_mov.z = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_mov.z -= PLAYER_ACCEL;
		if (m_mov.z < -PLAYER_SPEED)
		{
			m_mov.z = -PLAYER_SPEED;
		}
	}
	else
	{
		m_mov.z *= 0.95f;
	}

	if( PushHitKey( KEY_INPUT_SPACE ) ){
		m_mov.y = 0.3f;
	}

	m_pos += m_mov;

	//Bounce 

	if (m_pos.x < STAGE_X_MIN)
	{
		m_pos.x = STAGE_X_MIN;
		m_mov.x *= -1.0f;

	}
	else if(m_pos.x > STAGE_X_MAX)
	{
		m_pos.x = STAGE_X_MAX;
		m_mov.x *= -1.0f;

	}
	if (m_pos.z < STAGE_Z_MIN)
	{
		m_pos.z = STAGE_Z_MIN;
		m_mov.z *= -1.0f;

	}
	else if(m_pos.z > STAGE_Z_MAX)
	{
		m_pos.z = STAGE_Z_MAX;
		m_mov.z *= -1.0f;
	}


	if (m_pos.y <= 0.0f)
	{
		m_pos.y = 0.0f;
		m_mov.y *= -0.5f;
	}

	m_mov.y -= 0.02f;
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
