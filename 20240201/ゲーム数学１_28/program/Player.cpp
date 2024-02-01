#include "Main.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	    0.1f
#define PLAYER_MOV_SPEED_FAST	0.3f
#define PLAYER_ROT_SPEED	    3.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	���E�L�[�Ō����̕ύX
	float player_speed = PLAYER_MOV_SPEED;
	if (CheckHitKey(KEY_INPUT_LSHIFT)) { player_speed = PLAYER_MOV_SPEED_FAST; }

	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_rot.y += PLAYER_ROT_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_rot.y -= PLAYER_ROT_SPEED;
	}
	//	��L�[�Ō����Ă�������Ɉړ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.x += player_speed * sinf( TO_RADIAN( m_rot.y ) );
		m_pos.z += player_speed * cosf( TO_RADIAN( m_rot.y ) );
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
