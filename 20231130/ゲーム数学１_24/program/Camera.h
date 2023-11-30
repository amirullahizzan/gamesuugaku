#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	カメラクラス
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

	void Init();		//	初期化処理
	void Update(Float3 player_pos);		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
