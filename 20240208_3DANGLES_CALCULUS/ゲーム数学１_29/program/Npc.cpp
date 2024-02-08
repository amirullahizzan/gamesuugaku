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
	//	初期座標の設定
	m_pos.set( 0.0f, 0.0f, 5.0f );
	//	初期向きの設定
	m_rot.set( 0.0f, 90.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update(Float3 _player_pos)
{
	Float3 dir = _player_pos - m_pos;
	float destination_rot_y = TO_DEGREE(atan2f(dir.x,dir.z));
	float next_rot_y = destination_rot_y - m_rot.y;
	clsDx();
	printfDx("%f\n",destination_rot_y);
	printfDx("%f\n",m_rot.y);
	printfDx("%f",next_rot_y);

	while(next_rot_y >= 180.0f){		next_rot_y -= 360.0f;	}
	while(next_rot_y < -180.0f){		next_rot_y += 360.0f;	}

	if (next_rot_y >= NPC_ROT_SPEED)
	{
		m_rot.y += NPC_ROT_SPEED;
	}
	else if(next_rot_y <= -NPC_ROT_SPEED)
	{
		m_rot.y -= NPC_ROT_SPEED;
	}
	else
	{
		m_rot.y = destination_rot_y;
	}

	m_pos.x += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot.y));
	m_pos.z += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot.y));
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	モデルの座標を設定する
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	モデルの向きを設定する
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	モデルを描画する
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
