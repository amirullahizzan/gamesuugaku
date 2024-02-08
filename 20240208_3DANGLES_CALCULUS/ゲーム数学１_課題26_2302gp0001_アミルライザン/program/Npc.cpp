#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//	�m�o�b�̈ړ��X�s�[�h
#define NPC_MOV_SPEED	0.03f
//	�m�o�b�̉�]�X�s�[�h�i�x�j
#define NPC_ROT_SPEED	0.5f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	//	�n���ꂽ�f�[�^�ԍ����󂯎��
	m_model = model;
	//	�������W�̐ݒ�
	m_pos.set( 0.0f, 0.0f, 5.0f );
	//	���������̐ݒ�i�x���̉�]�p�x���X�O�x�ɂ��Ă��܂��j
	float random_rot_y = GetRand(361);
	//m_rot.set( 0.0f, 90.0f, 0.0f );
	m_rot.set( 0.0f, random_rot_y, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//	�v���C���[���W���󂯎��`�ɂ��܂�
//---------------------------------------------------------------------------------
void Npc::Update( Float3 player_pos )
{
	//	������ς��č��W�ړ�

	//	�P�F���̍��W�i m_pos �j�ƖڕW���W�i player_pos �j����ǂ̕����i�p�x�j�ɂȂ邩���߂�
	//	�P�|�P�F���̍��W����ڕW���W�܂ł̕����x�N�g�������߂�
	Float3 dir = player_pos - m_pos;
	//	�P�|�Q�F���̃x�N�g���i�̂w�y�j���g���Ċp�x�i�x���́j�����߂�
	//	���߂����p�x�͂x���̉�]�p�x�i���̂��߂Ƀx�N�g���̂w�y�̒l���g���Ċp�x�����߂܂��j
	//	atan2f �� GetRadian_LengthYX �Ɠ����֐��ł�
	float goal_roty = TO_DEGREE( atan2f( dir.x, dir.z ) );

	//	�Q�F���̌�������ڕW�̌����܂łǂ̂��炢�̊p�x�̍������邩
	float next_roty = goal_roty - m_rot.y;
	//	��ŋ��߂��p�x�̍��Ȃ�ł����m�o�b�̌����ƃv���C���[�Ƃ̌����̏󋵂ɂ���Ă�
	//	�߂�����傫���Ȃ����菬�����Ȃ����肷��\��������
	//	�Ȃ̂ŁA���̊p�x�� -180.0f �` 180.0f �ɂ�����
	//	�P�W�O�x���z���Ă���ꍇ�͂P�����i�R�U�O�x�j����
	while( next_roty >= 180.0f )	next_roty -= 360.0f;
	while( next_roty < -180.0f )	next_roty += 360.0f;

	//	�R�F�p�x�̍������ĉ�]�����܂�
	if( next_roty >= NPC_ROT_SPEED ){			//	���̍�����]�X�s�[�h�ȏ゠������
		m_rot.y += NPC_ROT_SPEED;				//	���̃X�s�[�h�Ńv���X��]������
	}else if( next_roty <= -NPC_ROT_SPEED ){	//	��]�X�s�[�h�����}�C�i�X
		m_rot.y -= NPC_ROT_SPEED;				//	�}�C�i�X��]������
	}else{										//	����Ȃ����i�قڐ��ʂ̎��j
		m_rot.y = goal_roty;					//	�ڕW�̌����ɂ���
	}

	//	�����Ă�������i m_rot.y �j�ɍ��W�ړ��i�w�y�����j
	//	�y������̊p�x�ɑ΂��Č������̒������~�����̂� sinf
	m_pos.x += NPC_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
	//	�p�x�ɉ��������̒����Ȃ̂� cosf
	m_pos.z += NPC_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	���f���̍��W��ݒ肷��
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	���f���̌�����ݒ肷��
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	���f����`�悷��
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
