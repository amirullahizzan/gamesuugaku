#include "Main.h"
#include "Game.h"
#include "Player.h"

#define PLAYER_ADD_SPEED	0.2f
#define PLAYER_MOV_SPEED	5.0f

//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	m_image = image;

	m_pos.set( 200.0f, 300.0f );
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Player::Update()
{
	static bool isGround = false;
	if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		m_mov.x += PLAYER_ADD_SPEED;
		if (m_mov.x > PLAYER_MOV_SPEED) { m_mov.x = PLAYER_MOV_SPEED; }
	}
	else if( CheckHitKey( KEY_INPUT_LEFT ) )
	{
		m_mov.x -= PLAYER_ADD_SPEED;
		if (m_mov.x < -PLAYER_MOV_SPEED) { m_mov.x = -PLAYER_MOV_SPEED; }
	}
	else
	{
		if (m_mov.x > 0.0f) { m_mov.x -= PLAYER_ADD_SPEED; if (m_mov.x < 0.0f) { m_mov.x = 0.0f; } }
		if(m_mov.x < 0.0f){ m_mov.x += PLAYER_ADD_SPEED; if (m_mov.x > 0.0f) { m_mov.x = 0.0f; } }
	}
	if (PushHitKey(KEY_INPUT_SPACE) && isGround)
	{
		isGround = false;
		m_mov.y = -12.0f;
	}

	m_pos += m_mov;
	m_mov.y += 1.0f;
	if (m_pos.y > 300) { m_pos.y = 300; m_mov.y = 0; isGround = true; }
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
//void Player::Render()
//{
//	DrawGraphF( m_pos.x, m_pos.y, m_image, TRUE );
//}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
