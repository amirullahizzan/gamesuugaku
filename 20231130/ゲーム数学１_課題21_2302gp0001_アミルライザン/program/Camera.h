#pragma once

#include "Float3.h"

//	カメラタイプ
enum {
	TYPE_STAGE,		//	全体を見るカメラ
	TYPE_PLAYER,	//	プレイヤーを見るカメラ
};

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	カメラ座標
	Float3	m_pos;
	//	見る座標
	Float3	m_look;

	//	カメラタイプ
	int		m_type;

	void Init();		//	初期化処理
	//	座標を受け取る形にします
	void Update( Float3 player_pos );		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
