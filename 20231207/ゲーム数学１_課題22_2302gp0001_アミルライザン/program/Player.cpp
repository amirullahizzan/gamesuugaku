#include "Main.h"
#include "Game.h"
#include "Player.h"

//	プレイヤーの移動スピード（ここまで上げていく）
#define PLAYER_SPEED	0.2f
//	加速スピード（この値分移動量を増やす）
#define PLAYER_ACCEL	0.005f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;
	m_pos.set( 0.0f, 0.0f, 0.0f );
	m_rot.set( 0.0f, 0.0f, 0.0f );
	//	プレイヤーモデルの半分の大きさ
	m_size.set( 0.5f, 0.5f, 0.5f );
	//	移動量無しで開始
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	左右キーでＸ方向の移動量を増やしたり減らしたり
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	右に移動させたいのでＸ方向の移動量を増やす
		m_mov.x += PLAYER_ACCEL;
		if( m_mov.x > PLAYER_SPEED ){
			m_mov.x = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_mov.x -= PLAYER_ACCEL;
		if( m_mov.x < -PLAYER_SPEED ){
			m_mov.x = -PLAYER_SPEED;
		}
	}else{
		//	左右キーを両方とも押していないときはＸ方向の移動量を 0.0f にする
		//	毎フレーム 0.95f をかけていくと限りなく 0.0f に近づく
		m_mov.x *= 0.95f;
	}

	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_mov.z += PLAYER_ACCEL;
		if( m_mov.z > PLAYER_SPEED ){
			m_mov.z = PLAYER_SPEED;
		}
	}else if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_mov.z -= PLAYER_ACCEL;
		if( m_mov.z < -PLAYER_SPEED ){
			m_mov.z = -PLAYER_SPEED;
		}
	}else{
		m_mov.z *= 0.95f;
	}

	//	スペースキーでジャンプ開始
	if( PushHitKey( KEY_INPUT_SPACE ) ){
		m_mov.y = 0.3f;
	}
	//	移動量を使った座標移動
	m_pos += m_mov;

	//	ステージの範囲まで行ったら座標はそこで止める（跳ね返る：移動方向を逆にする）
	if( m_pos.x < STAGE_X_MIN ){	//	左
		m_pos.x = STAGE_X_MIN;
		//	-1.0f をかけるとプラスとマイナスが入れ替わる（符号が反転する）
		m_mov.x *= -1.0f;
	}
	if( m_pos.x > STAGE_X_MAX ){	//	右
		m_pos.x = STAGE_X_MAX;
		m_mov.x *= -1.0f;
	}
	if( m_pos.z < STAGE_Z_MIN ){	//	手前
		m_pos.z = STAGE_Z_MIN;
		m_mov.z *= -1.0f;
	}
	if( m_pos.z > STAGE_Z_MAX ){	//	奥
		m_pos.z = STAGE_Z_MAX;
		m_mov.z *= -1.0f;
	}

	//	地面より下に行かないように
	if( m_pos.y <= 0.0f ){
		m_pos.y = 0.0f;
		//	このＹ方向の移動量を少し小さくして反転させる
		m_mov.y *= -0.5f;
	}
	//	Ｙ方向の移動量を下方向にするために減らしていく
	m_mov.y -= 0.02f;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	モデル番号を使って
	//	座標の設定
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	向きの設定
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	モデルの描画
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
