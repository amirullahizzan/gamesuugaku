#pragma once

#include "Float3.h"

//	�J�����^�C�v
enum {
	CAMERA_TYPE_STAGE,	//	�O�F�S�̂�����J����
	CAMERA_TYPE_PLAYER,	//	�P�F�v���C���[������J����
};

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:

	//	�J�������W
	Float3		m_pos;
	//	������W
	Float3		m_look;

	//	�J�����^�C�v
	int			m_type;

	void Init();		//	����������
	void Update( Float3 player_pos );		//	�X�V�����i���W���󂯎��l�ɕύX�j
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
