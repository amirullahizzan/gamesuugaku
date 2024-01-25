#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	基本クラス
//---------------------------------------------------------------------------------
class Base
{
public:
	int		m_model;	//	モデル番号

	Float3	m_pos;		//	座標
	Float3	m_rot;		//	向き


	void ScaleModel(float _scaleFactor);
	void ShrinkModel(float _scaleFactor);

	Float3 GetModelSize();
};