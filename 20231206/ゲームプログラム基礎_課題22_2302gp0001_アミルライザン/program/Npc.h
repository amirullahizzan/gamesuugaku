#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:
	Float2 m_mov;

	void Init( int image );		//	����������
	void Update();		//	�X�V����
//	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
