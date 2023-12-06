#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init( int image )
{
	m_image = image;

	m_pos.x = 700.0f;
	m_pos.y = 300.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update()
{
	if (m_pos.y > 300.0f) {
		m_pos.y = 300.0f;
		m_mov.y = 0.0f;
	}
	static float jumptimer = 0;
	if(jumptimer <= 0)
	{
		m_mov.y = -10.0f;
		jumptimer = (60*3); //jmpcooldown
	}

	if (jumptimer > 0)
	{
		jumptimer--;
	}

	//	Ｙ方向の移動量を毎フレーム少しずつ増やす
	m_mov.y += 0.3f;

	//	地面の高さ（ 300.0f ）よりは下に行かないように


	m_pos += m_mov;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
//void Npc::Render()
//{
//	DrawGraphF( m_pos.x, m_pos.y, m_image, TRUE );
//}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
