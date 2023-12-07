#include "Main.h"
#include "Game.h"
#include "Player.h"

//	�v���C���[�̈ړ��X�s�[�h�i�����܂ŏグ�Ă����j
#define PLAYER_SPEED	0.2f
//	�����X�s�[�h�i���̒l���ړ��ʂ𑝂₷�j
#define PLAYER_ACCEL	0.005f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;
	m_pos.set( 0.0f, 0.0f, 0.0f );
	m_rot.set( 0.0f, 0.0f, 0.0f );
	//	�v���C���[���f���̔����̑傫��
	m_size.set( 0.5f, 0.5f, 0.5f );
	//	�ړ��ʖ����ŊJ�n
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	���E�L�[�łw�����̈ړ��ʂ𑝂₵���茸�炵����
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	�E�Ɉړ����������̂łw�����̈ړ��ʂ𑝂₷
		m_mov.x += PLAYER_ACCEL;
		if( m_mov.x > PLAYER_SPEED ){
			m_mov.x = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_mov.x -= PLAYER_ACCEL;
		if( m_mov.x < -PLAYER_SPEED ){
			m_mov.x = -PLAYER_SPEED;
		}
	}else{
		//	���E�L�[�𗼕��Ƃ������Ă��Ȃ��Ƃ��͂w�����̈ړ��ʂ� 0.0f �ɂ���
		//	���t���[�� 0.95f �������Ă����ƌ���Ȃ� 0.0f �ɋ߂Â�
		m_mov.x *= 0.95f;
	}

	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_mov.z += PLAYER_ACCEL;
		if( m_mov.z > PLAYER_SPEED ){
			m_mov.z = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_mov.z -= PLAYER_ACCEL;
		if( m_mov.z < -PLAYER_SPEED ){
			m_mov.z = -PLAYER_SPEED;
		}
	}else{
		m_mov.z *= 0.95f;
	}

	//	�X�y�[�X�L�[�ŃW�����v�J�n
	if( PushHitKey( KEY_INPUT_SPACE ) ){
		m_mov.y = 0.3f;
	}
	//	�ړ��ʂ��g�������W�ړ�
	m_pos += m_mov;

	//	�X�e�[�W�͈̔͂܂ōs��������W�͂����Ŏ~�߂�i���˕Ԃ�F�ړ��������t�ɂ���j
	if( m_pos.x < STAGE_X_MIN ){	//	��
		m_pos.x = STAGE_X_MIN;
		//	-1.0f ��������ƃv���X�ƃ}�C�i�X������ւ��i���������]����j
		m_mov.x *= -1.0f;
	}
	if( m_pos.x > STAGE_X_MAX ){	//	�E
		m_pos.x = STAGE_X_MAX;
		m_mov.x *= -1.0f;
	}
	if( m_pos.z < STAGE_Z_MIN ){	//	��O
		m_pos.z = STAGE_Z_MIN;
		m_mov.z *= -1.0f;
	}
	if( m_pos.z > STAGE_Z_MAX ){	//	��
		m_pos.z = STAGE_Z_MAX;
		m_mov.z *= -1.0f;
	}

	//	�n�ʂ�艺�ɍs���Ȃ��悤��
	if( m_pos.y <= 0.0f ){
		m_pos.y = 0.0f;
		//	���̂x�����̈ړ��ʂ��������������Ĕ��]������
		m_mov.y *= -0.5f;
	}
	//	�x�����̈ړ��ʂ��������ɂ��邽�߂Ɍ��炵�Ă���
	m_mov.y -= 0.02f;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	���f���ԍ����g����
	//	���W�̐ݒ�
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	�����̐ݒ�
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	���f���̕`��
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
