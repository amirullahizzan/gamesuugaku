#include "Main.h"
#include "Game.h"
#include "Player.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init()
{
	//	プレイヤーモデルの読み込み
	m_model = MV1LoadModel( "data/player.mqoz" );
	//	初期座標の設定（３Ｄ空間上の原点）
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	//	初期向きの設定（回転無し）
	m_rot.x = 0.0f;
	m_rot.y = 0.0f;
	m_rot.z = 0.0f;
	//	移動量のクリア
	m_mov.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	十字キーで移動
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		m_pos.x += 0.2f;
		m_rot.y = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		m_pos.x -= 0.2f;
		m_rot.y = -90.0f;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.z += 0.2f;
		m_rot.y = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		m_pos.z -= 0.2f;
		m_rot.y = 180.0f;
	}
	static const int max_jump_count = 2;
	static int jump_count = max_jump_count;

	//	スペースキーでジャンプ開始
	if( PushHitKey( KEY_INPUT_SPACE  ) && jump_count > 0){
		//	上に飛ばすように移動量を設定
		//	0.3：ジャンプ力
		m_mov.y = 0.3f;
		jump_count -= 1;
	}

	//	Ｙ座標は常に移動量を足す
	m_pos.y += m_mov.y;

	//	プレイヤーは地面より下に行かない
	if( m_pos.y <= 0.0f ){
		//	Ｙ座標 0.0f を地面とします
		m_pos.y = 0.0f;
		jump_count = max_jump_count;
	}

	//	Ｙ方向の移動量を下方向にするために減らしていきます
	//	0.02：重力
	m_mov.y -= 0.02f;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	３Ｄモデルの座標設定
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	３Ｄモデルの向き設定
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	３Ｄモデルの描画
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
	//	モデルの終了処理
	MV1DeleteModel( m_model );
}
