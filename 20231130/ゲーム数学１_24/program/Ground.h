#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	地面クラス
//---------------------------------------------------------------------------------
class Ground
{
public:

	int		m_model;
	Float3	m_pos;
	Float3	m_rot;

	void Init();		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
