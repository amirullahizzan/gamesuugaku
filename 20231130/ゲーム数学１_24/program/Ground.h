#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	�n�ʃN���X
//---------------------------------------------------------------------------------
class Ground
{
public:

	int		m_model;
	Float3	m_pos;
	Float3	m_rot;

	void Init();		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
