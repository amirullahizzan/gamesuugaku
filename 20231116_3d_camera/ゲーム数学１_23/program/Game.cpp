#include "Main.h"
#include "Game.h"
#include "Float3.h"

int ground_model;
int player_model;

#define PLAYER_SPEED	0.2f

Float3 player_pos;
Float3 player_rot;

Float3 camera_pos;
Float3 camera_look;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );

	player_pos.x = 0.0f;
	player_pos.y = 0.0f;
	player_pos.z = 0.0f;
	
	camera_pos.x = 0.0f;
	camera_pos.y = 10.0f;
	camera_pos.z = -15.0f;
	
	camera_look.x = 0.0f;
	camera_look.y = 0.0f;
	camera_look.z = 15.0f;

	player_rot.x = 0.0f;
	player_rot.y = 0.0f;
	player_rot.z = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int BLACK = GetColor(0, 0, 0);
int WHITE = GetColor(255, 255, 255);
int* color_ptr = &BLACK;
void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player_pos.x += PLAYER_SPEED;
		player_rot.y = 90;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_pos.x -= PLAYER_SPEED;
		player_rot.y = -90;

	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_pos.z += PLAYER_SPEED;
		player_rot.y = 0;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_pos.z -= PLAYER_SPEED;
		player_rot.y = -180;
	}

	if( CheckHitKey( KEY_INPUT_D ) ){
		camera_pos.x += PLAYER_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_A ) ){
		camera_pos.x -= PLAYER_SPEED;

	}
	if( CheckHitKey( KEY_INPUT_W ) ){
		camera_pos.z += PLAYER_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_S ) ){
		camera_pos.z -= PLAYER_SPEED;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------

void GameRender()
{
	
	SetCameraPositionAndTarget_UpVecY( VGet( camera_pos.x, camera_pos.y, camera_pos.z), VGet( camera_look.x+camera_pos.x, camera_look.y, camera_pos.z+camera_look.z) );

	MV1SetPosition( ground_model, VGet( 0.0f, 0.0f, 0.0f ) );
	MV1SetRotationXYZ( ground_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ) ) );
	MV1DrawModel( ground_model );

	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );

	MV1SetPosition( player_model, VGet( player_pos.x, player_pos.y, player_pos.z ) );
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( player_rot.x ), TO_RADIAN( player_rot.y ), TO_RADIAN( player_rot.z ) ) );
	MV1DrawModel( player_model );

	DrawString( 16, 16, "十字キー：プレイヤー移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　向きも変える", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "ＷＡＳＤ：カメラ移動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
}
