#include "Main.h"
#include "Game.h"
#include "Ground.h"

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Ground::Init( int model )
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Ground::Update()
{
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Ground::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );

	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );

	//	�X�e�[�W�͈͂̕`��
	VECTOR p0 = VGet( STAGE_X_MIN, 0.1f, STAGE_Z_MIN );
	VECTOR p1 = VGet( STAGE_X_MAX, 0.1f, STAGE_Z_MIN );
	VECTOR p2 = VGet( STAGE_X_MAX, 0.1f, STAGE_Z_MAX );
	VECTOR p3 = VGet( STAGE_X_MIN, 0.1f, STAGE_Z_MAX );
	//	�X�e�[�W�͈͂̐��̕`��
	DrawLine3D( p0, p1, GetColor( 255, 255, 0 ) );
	DrawLine3D( p1, p2, GetColor( 255, 255, 0 ) );
	DrawLine3D( p2, p3, GetColor( 255, 255, 0 ) );
	DrawLine3D( p3, p0, GetColor( 255, 255, 0 ) );

	//	�G���A�̕`��i�w�y���� 5.0 �` 15.0 �j
	p0 = VGet( AREA_X_MIN, 0.1f, AREA_Z_MIN );
	p1 = VGet( AREA_X_MAX, 0.1f, AREA_Z_MIN );
	p2 = VGet( AREA_X_MAX, 0.1f, AREA_Z_MAX );
	p3 = VGet( AREA_X_MIN, 0.1f, AREA_Z_MAX );
	//	�΂̃G���A�̐��̕`��
	DrawLine3D( p0, p1, GetColor( 0, 255, 0 ) );
	DrawLine3D( p1, p2, GetColor( 0, 255, 0 ) );
	DrawLine3D( p2, p3, GetColor( 0, 255, 0 ) );
	DrawLine3D( p3, p0, GetColor( 0, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Ground::Exit()
{
}
