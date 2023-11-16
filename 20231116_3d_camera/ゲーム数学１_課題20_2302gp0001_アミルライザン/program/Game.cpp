#include "Main.h"
#include "Game.h"
#include "Float3.h"

//	�n�ʃ��f���p�̕ϐ�
int ground_model;
//	�v���C���[���f���p�̕ϐ�
int player_model;

//	�v���C���[�X�s�[�h�i����̃J�����⃂�f�����g�����v���W�F�N�g�ł̂��������̃X�s�[�h�j
#define PLAYER_SPEED	0.2f
//	�v���C���[���W�i�R�c��ԏ�̍��W�Ƃ��Ďg���̂� Float3 �Ő錾���Ă��܂��j
Float3 player_pos;
//	�v���C���[�̌����i���f���̉�]�͂w�x�y�̂R���ŉ�]�ł���̂� Float3 �Łj
Float3 player_rot;

//	�J�����̈ړ��X�s�[�h
#define CAMERA_SPEED	0.1f
//	�J�������W�i�R�c��ԏ�̃J�������ǂ��ɒu�����j
Float3 camera_pos;

//	������W�i�R�c��ԏ�̂ǂ������邩�j
Float3 camera_look;

Float3 center_pos;
Float3 center_look;

Float3* camera_pos_ptr = &camera_pos;
Float3* camera_look_ptr = &camera_look;

Float3 rendercampos;
Float3 rendercamlook;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�n�ʃ��f����ǂݍ���Ŕԍ����擾
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	//	�v���C���[���f���̓ǂݍ���
	player_model = MV1LoadModel( "data/player.mqoz" );

	//	�v���C���[�̏������W�̐ݒ�i�R�c��ԏ�̌��_�j
	player_pos.x = 0.0f;
	player_pos.y = 0.0f;
	player_pos.z = 0.0f;
	//	�v���C���[�̌����i��]���Ă��Ȃ���ԂŊJ�n�j
	player_rot.x = 0.0f;
	player_rot.y = 0.0f;
	player_rot.z = 0.0f;

	//	�J�������W�̏����ݒ�
	camera_pos.x =   0.0f;
	camera_pos.y =  3.0f;
	camera_pos.z = -10.0f;
	//	������W
	camera_look.x = 0.0f;
	camera_look.y = 0.0f;
	camera_look.z = 15.0f;
	
	rendercampos.x =   0.0f;
	rendercampos.y =  -3.0f;
	rendercampos.z = 0.0f;
	//	������W
	rendercamlook.x = 0.0f;
	rendercamlook.y = 0.0f;
	rendercamlook.z = 15.0f;
	
	center_pos.x =  0.0f;
	center_pos.y = 20.0f;
	center_pos.z = -50.0f;
	//	������W
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
//	�X�V����
//---------------------------------------------------------------------------------
static bool cam_followPlayer = true;

void GameUpdate()
{
	//	�E�L�[�������Ă���Ƃ��̓v���C���[���E�i��ʓI�Ɂj�Ɉړ���������
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	����̃J�������猩���E�͂w�v���X����
		player_pos.x += PLAYER_SPEED;
		//	�E�Ɉړ�����̂ŉE�Ɍ���������
		player_rot.y = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_pos.x -= PLAYER_SPEED;
		player_rot.y = -90.0f;
	}
	//	��L�[�����������ʂ̉��ɐi�݂���
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	�J�������猩�����͂y�v���X����
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
//	�`�揈��
//---------------------------------------------------------------------------------


void GameRender()
{
	//	�J�������W�i camera_pos �j�ƌ�����W�i camera_look �j��n���ăJ�����ݒ�
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

	//	�n�ʃ��f���̍��W�ݒ�i�R�c��ԏ�̌��_�j
	MV1SetPosition( ground_model, VGet( 0.0f, 0.0f, 0.0f ) );
	//	�n�ʃ��f���̌�����ݒ�
	MV1SetRotationXYZ( ground_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ) ) );
	//	�n�ʃ��f���̕`��
	MV1DrawModel( ground_model );

	//	�ڈ��Ƃ��Ăw���Ƃy���ɐ��������܂�
	//	�w���ɐԂ���
	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	//	�y���ɐ���
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );

	//	�v���C���[�̍��W�������ݒ肵�ă��f���̕`��
	//	���W��ݒ�
	MV1SetPosition( player_model, VGet( player_pos.x, player_pos.y, player_pos.z ) );
	//	������ݒ�
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( player_rot.x ), TO_RADIAN( player_rot.y ), TO_RADIAN( player_rot.z ) ) );
	//	���f����`��
	MV1DrawModel( player_model );

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�������ς���", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�v���C���[�ɂ��Ă����J����", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
}
