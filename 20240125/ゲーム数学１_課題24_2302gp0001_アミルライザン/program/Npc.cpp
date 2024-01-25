#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//	ＮＰＣの移動スピード
#define NPC_MOV_SPEED	0.03f
//	ＮＰＣの回転スピード（度）
#define NPC_ROT_SPEED	0.5f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	//	渡されたデータ番号を受け取る
	m_model = model;
	//	初期座標設定
	float randomPosModifier = 10;
	float randomRotModifier = 360;
	float randomPos = GetRandomF(-randomPosModifier, randomPosModifier);
	float randomRotY = GetRandomF(-randomRotModifier, randomRotModifier);
	m_pos.set(randomPos, 0.0f, randomPos);
	//	初期向きの設定（３軸回転角度全て０度）
	m_rot.set( 0.0f, randomRotY, 0.0f);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update()
{
	//	回転させる（Ｙ軸回転させる：右回転はプラス方向の回転）
	m_rot.y += NPC_ROT_SPEED;

	m_pos.x += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot.y));
	//	Ｚ方向は、Ｚ軸からの角度（ m_rot.y ）に対して沿っている方の長さ分移動
	m_pos.z += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot.y));
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	モデルの座標を設定
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	モデルの向きを設定
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	モデルの描画をする
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
