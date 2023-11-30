#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player
{
private :
	enum DIR
	{
		RIGHT, LEFT, UP, DOWN
	};

	void DampenRotation(float _desired_angle, float _dampen_speed);
	void DampenRotateUpdate();
	int m_DIR_switch = 0;
public:

	int		m_model;
	Float3	m_pos;
	Float3	m_rot;
	//force
	Float3	m_mov;

	void Init();		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
