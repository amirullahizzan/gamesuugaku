#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//	ＮＰＣの移動スピード
#define NPC_SPEED	0.3f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	m_model = model;

	m_rot.set( 0.0f, 180.0f, 0.0f );
	m_size.set( 0.5f, 0.5f, 0.5f );
	//	ランダム設定
	SetRandom();
	m_mov.x = NPC_SPEED;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update()
{
	if (m_pos.x < STAGE_X_MIN) {	//	左
		m_pos.x = STAGE_X_MIN;
		//	-1.0f をかけるとプラスとマイナスが入れ替わる（符号が反転する）
		m_mov.x *= -1.0f;
	}
	if (m_pos.x > STAGE_X_MAX) {	//	右
		m_pos.x = STAGE_X_MAX;
		m_mov.x *= -1.0f;
	}

	m_pos += m_mov;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}

//---------------------------------------------------------------------------------
//	座標のランダムな設定
//---------------------------------------------------------------------------------
void Npc::SetRandom()
{
	//	ステージの中のどこかに座標をランダムに設定
	m_pos.set( GetRandomF( STAGE_X_MIN, STAGE_X_MAX ), 0.0f, GetRandomF( STAGE_Z_MIN, STAGE_Z_MAX ) );
}
