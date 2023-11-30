#include "Main.h"
#include "Game.h"
#include "Camera.h"

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	�J�������W�̏����ݒ�
	//	x = 0.0f y = 20.0f z = -30.0f
	m_pos.set( 0.0f, 20.0f, -30.0f );
	//	������W�̏����ݒ�
	//	x = 0.0f y = 0.0f z = 0.0f
	m_look.clear();
	//	�S�̂�����J�����ŊJ�n
	m_type = TYPE_STAGE;
}
//---------------------------------------------------------------------------------
//	�X�V�����i���W���󂯎���悤�Ɉ����ǉ��j
//---------------------------------------------------------------------------------
void Camera::Update( Float3 player_pos )
{
	//	�e�P�E�e�Q�L�[�ŃJ�����^�C�v�̐؂�ւ�
	if( PushHitKey( KEY_INPUT_F1 ) )	m_type = TYPE_STAGE;
	if( PushHitKey( KEY_INPUT_F2 ) )	m_type = TYPE_PLAYER;

	const float MAX_Y_LOOK = 0;

	//	�^�C�v�ɂ���ăJ�������W�〈����W�̐ݒ�𕪂��܂�
	switch( m_type ){
	case TYPE_STAGE:
		//	�J�������W
		m_pos.set( 0.0f, 20.0f, -30.0f );
		//	������W
		m_look.clear();
		break;

	case TYPE_PLAYER:
		//	������W�̓v���C���[���W
		//	�J�������W�͌�����W�����藣�ꂽ�Ƃ���
		
		m_look.set( player_pos );
		m_pos.x = m_look.x +  0.0f;
		m_pos.z = m_look.z - 15.0f;
		if (player_pos.y > 0)
		{
			//m_pos.y = 0;
			m_look.y = 0;
		}
		m_pos.y = m_look.y + 7.0f;
		break;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	�J�������W�ƌ�����W��n���ăJ�����ݒ�
	SetCameraPositionAndTarget_UpVecY( VGet( m_pos.x, m_pos.y, m_pos.z ), VGet( m_look.x, m_look.y, m_look.z ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
