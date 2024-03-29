#include "Main.h"
#include "Game.h"
#include "Camera.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	カメラの座標の初期設定
	m_pos.set( 0.0f, 20.0f, -30.0f );
	//	見る座標は原点
	m_look.clear();

	//	全体を見るカメラで開始
	m_type = CAMERA_TYPE_STAGE;
}
//---------------------------------------------------------------------------------
//	更新処理（座標を受け取る形に変更）
//---------------------------------------------------------------------------------
void Camera::Update( Float3 player_pos )
{
	if( CheckHitKey( KEY_INPUT_F1 ) )	m_type = CAMERA_TYPE_STAGE;		//	Ｆ１キーで全体カメラ
	if( CheckHitKey( KEY_INPUT_F2 ) )	m_type = CAMERA_TYPE_PLAYER;	//	Ｆ２キーでプレイヤーカメラ

	//	カメラタイプに合わせてカメラ座標と見る座標を設定する
	switch( m_type ){
	case CAMERA_TYPE_STAGE:	//	全体カメラ
		m_pos.set( 0.0f, 20.0f, -30.0f );
		m_look.clear();
		break;

	case CAMERA_TYPE_PLAYER:	//	プレイヤーカメラ
		//	見る座標は受け取った座標にします
		m_look.set( player_pos );

		//	カメラの見る座標の高さは地面の高さに
		m_look.y = 0.0f;

		//	カメラ座標は見る座標から一定離れたところ
		m_pos.x = m_look.x +  0.0f;
		m_pos.y = m_look.y +  7.0f;
		m_pos.z = m_look.z - 15.0f;
		break;
	case CAMERA_TYPE_AREA:


		break;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	モデルの描画開始時にカメラの座標と見る座標を渡してカメラ設定
	SetCameraPositionAndTarget_UpVecY( VGet( m_pos.x, m_pos.y, m_pos.z ), VGet( m_look.x, m_look.y, m_look.z ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
