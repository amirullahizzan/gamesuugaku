#pragma once

#include "Float3.h"

//	カメラタイプ


//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	enum {
		CAMERA_TYPE_STAGE,	//	０：全体を見るカメラ
		CAMERA_TYPE_PLAYER,	//	１：プレイヤーを見るカメラ
		CAMERA_TYPE_AREA // 2
	};
	//	カメラ座標
	Float3		m_pos;
	//	見る座標
	Float3		m_look;

	//	カメラタイプ
	int			m_type;

	void Init();		//	初期化処理
	void Update( Float3 player_pos );		//	更新処理（座標を受け取る様に変更）
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
