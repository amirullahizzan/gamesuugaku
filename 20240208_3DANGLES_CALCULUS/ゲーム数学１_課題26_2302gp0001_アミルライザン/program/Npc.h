#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int model );		//	����������

	//	�v���C���[���W���󂯎��`�ɂ��܂�
	void Update( Float3 player_pos );		//	�X�V����

	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
