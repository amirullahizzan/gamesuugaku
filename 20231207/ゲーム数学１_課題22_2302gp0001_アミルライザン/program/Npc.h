#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:
	Float3 m_mov;
	void Init( int model );		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理

	void SetRandom();
};
