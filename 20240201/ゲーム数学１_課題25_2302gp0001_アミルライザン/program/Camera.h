#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:

	Float3	m_pos;		//	�J�������W
	Float3	m_look;		//	������W

	void Init();		//	����������
	void Update( Float3 player_pos );		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
