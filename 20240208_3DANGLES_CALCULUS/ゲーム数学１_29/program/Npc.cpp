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
	//	���������̐ݒ�
	m_rot.set( 0.0f, 90.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Npc::Update(Float3 _player_pos)
{
	Float3 dir = _player_pos - m_pos;
	float destination_rot_y = TO_DEGREE(atan2f(dir.x,dir.z));
	float next_rot_y = destination_rot_y - m_rot.y;
	clsDx();
	printfDx("%f\n",destination_rot_y);
	printfDx("%f\n",m_rot.y);
	printfDx("%f",next_rot_y);

	while(next_rot_y >= 180.0f){		next_rot_y -= 360.0f;	}
	while(next_rot_y < -180.0f){		next_rot_y += 360.0f;	}

	if (next_rot_y >= NPC_ROT_SPEED)
	{
		m_rot.y += NPC_ROT_SPEED;
	}
	else if(next_rot_y <= -NPC_ROT_SPEED)
	{
		m_rot.y -= NPC_ROT_SPEED;
	}
	else
	{
		m_rot.y = destination_rot_y;
	}

	m_pos.x += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot.y));
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
