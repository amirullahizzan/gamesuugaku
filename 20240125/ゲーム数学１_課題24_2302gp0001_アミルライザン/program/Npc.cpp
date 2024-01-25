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
	//	�������W�ݒ�
	float randomPosModifier = 10;
	float randomRotModifier = 360;
	float randomPos = GetRandomF(-randomPosModifier, randomPosModifier);
	float randomRotY = GetRandomF(-randomRotModifier, randomRotModifier);
	m_pos.set(randomPos, 0.0f, randomPos);
	//	���������̐ݒ�i�R����]�p�x�S�ĂO�x�j
	m_rot.set( 0.0f, randomRotY, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Npc::Update()
{
	//	��]������i�x����]������F�E��]�̓v���X�����̉�]�j
	m_rot.y += NPC_ROT_SPEED;

	m_pos.x += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot.y));
	//	�y�����́A�y������̊p�x�i m_rot.y �j�ɑ΂��ĉ����Ă�����̒������ړ�
	m_pos.z += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot.y));
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	���f���̍��W��ݒ�
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	���f���̌�����ݒ�
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	���f���̕`�������
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
