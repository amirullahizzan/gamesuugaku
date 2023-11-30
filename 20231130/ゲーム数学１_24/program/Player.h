#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
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

	void Init();		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
