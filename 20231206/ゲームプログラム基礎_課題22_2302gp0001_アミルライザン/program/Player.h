#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	�ړ���
	Float2	m_mov;

	void Init( int image );		//	����������
	void Update();		//	�X�V����
//	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
