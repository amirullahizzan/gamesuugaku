#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
private:
	enum
	{
		TYPE_STAGE, TYPE_PLAYER
	};
public:

	Float3	m_pos;
	Float3	m_look;
	int m_camera_type = TYPE_STAGE;

	void Init();		//	����������
	void Update(Float3 player_pos);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
