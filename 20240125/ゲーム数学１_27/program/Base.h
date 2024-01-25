#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	��{�N���X
//---------------------------------------------------------------------------------
class Base
{
public:
	int		m_model;	//	���f���ԍ�

	Float3	m_pos;		//	���W
	Float3	m_rot;		//	����


	void ScaleModel( float _scaleFactor);
	void ShrinkModel(float _scaleFactor);

	Float3 GetModelSize();
};
