#include "Main.h"
#include "Game.h"
#include "Player.h"

void Player::DampenRotation(float _desired_angle, float _dampen_speed)
{
	float diff = _desired_angle - m_rot.y;
	diff = fmodf(diff + 360, 360); // Normalize the difference between angles

	if (diff > 180)
	{
		diff -= 360; // Choose the shorter path by adjusting the difference
	}

	if (diff > 0 && diff <= _dampen_speed)
	{
		m_rot.y = _desired_angle;
	}
	else if (diff < 0 && -diff <= _dampen_speed)
	{
		m_rot.y = _desired_angle;
	}
	else if (diff > 0)
	{
		m_rot.y += _dampen_speed;
	}
	else if (diff < 0)
	{
		m_rot.y -= _dampen_speed;
	}
}

void Player::DampenRotateUpdate()
{
	const float dampen_speed = 8;

	switch (m_DIR_switch)
	{
	case RIGHT:
		DampenRotation(90,dampen_speed);
		break;
	case LEFT:
		DampenRotation(270, dampen_speed);
		break;
	case UP:
		DampenRotation(0, dampen_speed);
		break;
	case DOWN:
		DampenRotation(180, dampen_speed);
		break;
	}

}

//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void Player::Init()
{
	m_model = MV1LoadModel( "data/player.mqoz" );

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;

	m_rot.x = 0.0f;
	m_rot.y = 0.0f;
	m_rot.z = 0.0f;
}
//---------------------------------------------------------------------------------
//	XVˆ—
//---------------------------------------------------------------------------------
void Player::Update()
{
	DampenRotateUpdate();
	const float speed = 0.2f;
	if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		m_pos.x += speed;
		m_DIR_switch = DIR::RIGHT;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) )
	{
		m_pos.x -= speed;
		m_DIR_switch = DIR::LEFT;
	}
	if( CheckHitKey( KEY_INPUT_UP ) )
	{
		m_pos.z += speed;
		m_DIR_switch = DIR::UP;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) )
	{
		m_pos.z -= speed;
		m_DIR_switch = DIR::DOWN;
	}

		const float gravity = 0.2f;
	if( PushHitKey( KEY_INPUT_SPACE ) )
	{
		//jmp
		m_mov.y = 0.5f;
	}

	m_pos.y += m_mov.y;

	if (m_pos.y <= 0) { m_pos.y = 0.0f; }
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
	MV1DeleteModel( m_model );
}
