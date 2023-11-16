#include "Main.h"
#include "Game.h"
#include "Float3.h"

//	地面モデル用の変数
int ground_model;
//	プレイヤーモデル用の変数
int player_model;

//	プレイヤースピード（今回のカメラやモデルを使ったプロジェクトでのいい感じのスピード）
#define PLAYER_SPEED	0.2f
//	プレイヤー座標（３Ｄ空間上の座標として使うので Float3 で宣言しています）
Float3 player_pos;
//	プレイヤーの向き（モデルの回転はＸＹＺの３軸で回転できるので Float3 で）
Float3 player_rot;

//	カメラの移動スピード
#define CAMERA_SPEED	0.1f
//	カメラ座標（３Ｄ空間上のカメラをどこに置くか）
Float3 camera_pos;

//	見る座標（３Ｄ空間上のどこを見るか）
Float3 camera_look;

Float3 center_pos;
Float3 center_look;

Float3* camera_pos_ptr = &camera_pos;
Float3* camera_look_ptr = &camera_look;

Float3 rendercampos;
Float3 rendercamlook;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	地面モデルを読み込んで番号を取得
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	//	プレイヤーモデルの読み込み
	player_model = MV1LoadModel( "data/player.mqoz" );

	//	プレイヤーの初期座標の設定（３Ｄ空間上の原点）
	player_pos.x = 0.0f;
	player_pos.y = 0.0f;
	player_pos.z = 0.0f;
	//	プレイヤーの向き（回転していない状態で開始）
	player_rot.x = 0.0f;
	player_rot.y = 0.0f;
	player_rot.z = 0.0f;

	//	カメラ座標の初期設定
	camera_pos.x =   0.0f;
	camera_pos.y =  3.0f;
	camera_pos.z = -10.0f;
	//	見る座標
	camera_look.x = 0.0f;
	camera_look.y = 0.0f;
	camera_look.z = 15.0f;
	
	rendercampos.x =   0.0f;
	rendercampos.y =  -3.0f;
	rendercampos.z = 0.0f;
	//	見る座標
	rendercamlook.x = 0.0f;
	rendercamlook.y = 0.0f;
	rendercamlook.z = 15.0f;
	
	center_pos.x =  0.0f;
	center_pos.y = 20.0f;
	center_pos.z = -50.0f;
	//	見る座標
	center_look.x = 0.0f;
	center_look.y = 0.0f;
	center_look.z = 40.0f;
}

void CamFollow(Float3& postarget, Float3& looktarget = camera_look)
{
	camera_pos_ptr = &postarget;
	camera_look_ptr = &looktarget;
};
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
static bool cam_followPlayer = true;

void GameUpdate()
{
	//	右キーを押しているときはプレイヤーを右（画面的に）に移動させたい
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	今回のカメラから見た右はＸプラス方向
		player_pos.x += PLAYER_SPEED;
		//	右に移動するので右に向かせたい
		player_rot.y = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_pos.x -= PLAYER_SPEED;
		player_rot.y = -90.0f;
	}
	//	上キーを押したら画面の奥に進みたい
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	カメラから見た奥はＺプラス方向
		player_pos.z += PLAYER_SPEED;
		player_rot.y = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_pos.z -= PLAYER_SPEED;
		player_rot.y = 180.0f;
	}




	if (CheckHitKey(KEY_INPUT_F1))
	{
		cam_followPlayer = true;
	}
	if (CheckHitKey(KEY_INPUT_F2))
	{
		cam_followPlayer = false;
	}


	if (cam_followPlayer)
	{
		/*camera_pos.x = player_pos.x;
		camera_pos.y = player_pos.y + 3.0f;
		camera_pos.z = player_pos.z + (-10.0f);*/
		CamFollow(player_pos);

	}
	else
	{
		CamFollow(center_pos,center_look);

	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------


void GameRender()
{
	//	カメラ座標（ camera_pos ）と見る座標（ camera_look ）を渡してカメラ設定
	clsDx();
	printfDx("rendercampos %f" , rendercampos.y);
	printfDx("rendercampos %f" , rendercamlook.y);
	rendercampos = *camera_pos_ptr;
	rendercamlook = *camera_look_ptr;
	if (cam_followPlayer)
	{
		rendercampos.x = player_pos.x;
		rendercampos.y +=  3.0f;
		rendercampos.z +=  (-10.0f);
	}
	
	SetCameraPositionAndTarget_UpVecY( VGet( rendercampos.x, rendercampos.y, rendercampos.z ), 
		VGet(rendercamlook.x+ rendercampos.x, rendercamlook.y, rendercamlook.z + rendercampos.z) );

	//	地面モデルの座標設定（３Ｄ空間上の原点）
	MV1SetPosition( ground_model, VGet( 0.0f, 0.0f, 0.0f ) );
	//	地面モデルの向きを設定
	MV1SetRotationXYZ( ground_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ) ) );
	//	地面モデルの描画
	MV1DrawModel( ground_model );

	//	目安としてＸ軸とＺ軸に線を引きます
	//	Ｘ軸に赤い線
	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	//	Ｚ軸に青い線
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );

	//	プレイヤーの座標や向きを設定してモデルの描画
	//	座標を設定
	MV1SetPosition( player_model, VGet( player_pos.x, player_pos.y, player_pos.z ) );
	//	向きを設定
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( player_rot.x ), TO_RADIAN( player_rot.y ), TO_RADIAN( player_rot.z ) ) );
	//	モデルを描画
	MV1DrawModel( player_model );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　向きも変える", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "プレイヤーについていくカメラ", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
}
