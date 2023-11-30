#pragma once

#include "Float3.h"

//	�J�����^�C�v
enum {
	TYPE_STAGE,		//	�S�̂�����J����
	TYPE_PLAYER,	//	�v���C���[������J����
};

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	�J�������W
	Float3	m_pos;
	//	������W
	Float3	m_look;

	//	�J�����^�C�v
	int		m_type;

	void Init();		//	����������
	//	���W���󂯎��`�ɂ��܂�
	void Update( Float3 player_pos );		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
