#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Player.h"

//	�v���C���[�̉����x
#define PLAYER_ADD_SPEED	0.2f
//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOV_SPEED	5.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	m_image = image;
	//	�������W�̐ݒ�i�Q�[�������W�j
	m_pos.set( 200.0f, 300.0f );
	//	�ړ��ʂ͍ŏ��͂O�ŊJ�n
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	�ړ��ʂ𑝂₵���茸�炵����
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){		//	�E�������Ă���Ƃ�
		//	�ړ��ʂ𑝂₵�Ă���
		m_mov.x += PLAYER_ADD_SPEED;
		if( m_mov.x > PLAYER_MOV_SPEED ){
			m_mov.x = PLAYER_MOV_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){	//	���������Ă���Ƃ�
		//	�ړ��ʂ����炵�Ă���
		m_mov.x -= PLAYER_ADD_SPEED;
		if( m_mov.x < -PLAYER_MOV_SPEED ){
			m_mov.x = -PLAYER_MOV_SPEED;
		}
	}else{	//	�ǂ���������Ă��Ȃ���
		//	�ړ��ʂ��O�ɂ��Ă���
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

	//	�X�y�[�X�L�[����������W�����v�J�n
	if( PushHitKey( KEY_INPUT_SPACE ) && iscanJump){
		//	�W�����v�͐ݒ�
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

	//	�ړ��ʕ����W�ړ�
	m_pos += m_mov;

	//	�x�����̈ړ��ʂ𖈃t���[�����������₷
	m_mov.y += 0.3f;

	//	�n�ʂ̍����i 300.0f �j���͉��ɍs���Ȃ��悤��
	if( m_pos.y > 300.0f ){
		m_pos.y = 300.0f;
		m_mov.y = 0.0f;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
//void Player::Render()
//{
//	DrawGraphF( m_pos.x, m_pos.y, m_image, TRUE );
//}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
