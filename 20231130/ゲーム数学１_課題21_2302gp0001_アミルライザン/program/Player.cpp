#include "Main.h"
#include "Game.h"
#include "Player.h"

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init()
{
	//	�v���C���[���f���̓ǂݍ���
	m_model = MV1LoadModel( "data/player.mqoz" );
	//	�������W�̐ݒ�i�R�c��ԏ�̌��_�j
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	//	���������̐ݒ�i��]�����j
	m_rot.x = 0.0f;
	m_rot.y = 0.0f;
	m_rot.z = 0.0f;
	//	�ړ��ʂ̃N���A
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	�\���L�[�ňړ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_pos.x += 0.2f;
		m_rot.y = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_pos.x -= 0.2f;
		m_rot.y = -90.0f;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.z += 0.2f;
		m_rot.y = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_pos.z -= 0.2f;
		m_rot.y = 180.0f;
	}
	static const int max_jump_count = 2;
	static int jump_count = max_jump_count;

	//	�X�y�[�X�L�[�ŃW�����v�J�n
	if( PushHitKey( KEY_INPUT_SPACE  ) && jump_count > 0){
		//	��ɔ�΂��悤�Ɉړ��ʂ�ݒ�
		//	0.3�F�W�����v��
		m_mov.y = 0.3f;
		jump_count -= 1;
	}

	//	�x���W�͏�Ɉړ��ʂ𑫂�
	m_pos.y += m_mov.y;

	//	�v���C���[�͒n�ʂ�艺�ɍs���Ȃ�
	if( m_pos.y <= 0.0f ){
		//	�x���W 0.0f ��n�ʂƂ��܂�
		m_pos.y = 0.0f;
		jump_count = max_jump_count;
	}

	//	�x�����̈ړ��ʂ��������ɂ��邽�߂Ɍ��炵�Ă����܂�
	//	0.02�F�d��
	m_mov.y -= 0.02f;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	�R�c���f���̍��W�ݒ�
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	�R�c���f���̌����ݒ�
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	�R�c���f���̕`��
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
	//	���f���̏I������
	MV1DeleteModel( m_model );
}
