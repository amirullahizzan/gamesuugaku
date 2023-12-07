#include "Main.h"
#include "Game.h"
#include "Ground.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Ground::Init( int model )
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Ground::Update()
{
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Ground::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );

	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );

	//	ステージ範囲の描画
	VECTOR p0 = VGet( STAGE_X_MIN, 0.1f, STAGE_Z_MIN );
	VECTOR p1 = VGet( STAGE_X_MAX, 0.1f, STAGE_Z_MIN );
	VECTOR p2 = VGet( STAGE_X_MAX, 0.1f, STAGE_Z_MAX );
	VECTOR p3 = VGet( STAGE_X_MIN, 0.1f, STAGE_Z_MAX );
	//	ステージ範囲の線の描画
	DrawLine3D( p0, p1, GetColor( 255, 255, 0 ) );
	DrawLine3D( p1, p2, GetColor( 255, 255, 0 ) );
	DrawLine3D( p2, p3, GetColor( 255, 255, 0 ) );
	DrawLine3D( p3, p0, GetColor( 255, 255, 0 ) );

	//	エリアの描画（ＸＺ共に 5.0 ～ 15.0 ）
	p0 = VGet( AREA_X_MIN, 0.1f, AREA_Z_MIN );
	p1 = VGet( AREA_X_MAX, 0.1f, AREA_Z_MIN );
	p2 = VGet( AREA_X_MAX, 0.1f, AREA_Z_MAX );
	p3 = VGet( AREA_X_MIN, 0.1f, AREA_Z_MAX );
	//	緑のエリアの線の描画
	DrawLine3D( p0, p1, GetColor( 0, 255, 0 ) );
	DrawLine3D( p1, p2, GetColor( 0, 255, 0 ) );
	DrawLine3D( p2, p3, GetColor( 0, 255, 0 ) );
	DrawLine3D( p3, p0, GetColor( 0, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Ground::Exit()
{
}
