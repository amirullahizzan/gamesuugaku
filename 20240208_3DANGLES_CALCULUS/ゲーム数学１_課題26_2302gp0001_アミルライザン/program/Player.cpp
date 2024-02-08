#include "Main.h"
#include "Player.h"

//	プレイヤーの移動スピード
#define PLAYER_MOV_SPEED	0.1f
//	プレイヤーの回転スピード（度）
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	//	渡されたデータ番号を受け取る
	m_model = model;
	//	初期座標設定
	m_pos.set( -5.0f, 0.0f, -5.0f );
	//	初期向きの設定（３軸回転角度全て０度）
	m_rot.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	左右キーを押したら向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_rot.y += PLAYER_ROT_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_rot.y -= PLAYER_ROT_SPEED;
	}

	//	上キーを押しているときは向いている方向に移動
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.x += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
		m_pos.z += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
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
void Player::Exit()
{
}
