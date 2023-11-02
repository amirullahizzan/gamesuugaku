#include "Main.h"
#include "Game.h"
#include "Random.h"

//	�m�o�b�̐�
#define	NPC_MAX	10

//	���f���f�[�^��ǂݍ��񂾎��ɂ��炦��ԍ�������p�̕ϐ�
int ground_model;	//	�n�ʃ��f��
int player_model;	//	�v���C���[���f��
int npc_model;		//	�m�o�b���f��

//	�v���C���[���W�ϐ�
float player_x;
float player_y;
float player_z;
int player_rota = 0;

//	�m�o�b�̍��W�ϐ�
#define MAX_ENEMY 10
float npc_x[MAX_ENEMY];
float npc_y[MAX_ENEMY];
float npc_z[MAX_ENEMY];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^��ǂݍ���Ŕԍ����擾
	ground_model = MV1LoadModel( "data/ground.mqoz" );	//	�n�ʃ��f��
	player_model = MV1LoadModel( "data/player.mqoz" );	//	�n�ʃ��f��
	npc_model = MV1LoadModel( "data/npc.mqoz" );	//	�n�ʃ��f��

	//	�v���C���[�������W�̐ݒ�
	player_x = 0.0f;
	player_y = 0.0f;
	player_z = 0.0f;

	//	�m�o�b�̏������W�̐ݒ�i�n�ʂ̎l�p�P�}�X�����j
	for (int i = 0 ;i < MAX_ENEMY;i++)
	{
	npc_x[i] = GetRandomF(-10.0f, 10.0f);
	npc_y[i] = 0.0f;
	npc_z[i] = GetRandomF(-10.0f, 10.0f);
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�Ńv���C���[�̍��W�ړ�
	//	�E�L�[�ŉE�ړ��i�J�������猩���E�Ɉړ��j
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += 0.2f;
		player_rota = 90;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= 0.2f;
		player_rota = -90;
	}
	//	��L�[�ňړ��i��ʂ̉��ɐi�܂������j
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_z += 0.2f;
		player_rota = 0;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_z -= 0.2f;
		player_rota = -180;
	}

	for (int i = 0; i < MAX_ENEMY; i++)
	{
	npc_z[i] -= 0.1f;
	//	���_����P�}�X����O�ɗ�����
	if( npc_z[i] < -10.0f ){
		//	�w���W�� -10.0f �` 10.0f �̃����_���Ȓl��
		npc_x[i] = GetRandomF( -10.0f, 10.0f );
		//	�y���W�͌��_����P�}�X������
		npc_z[i] = GetRandomF(-10.0f, 10.0f);
	}
	}
	//	�m�o�b�̍��W�ړ��i��ʎ�O�Ɉړ��j

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�i�J�������W�i�J�������ǂ��ɒu�����j�ƌ�����W�i���̃J�������ǂ������邩�j��n���Đݒ肷��j
	SetCameraPositionAndTarget_UpVecY( VGet( 0.0f, 10.0f, -20.0f ), VGet( 0.0f, 0.0f, 0.0f ) );

	//	���f���̕`��ꎮ
	//	���f���̍��W�ݒ�
	MV1SetPosition( ground_model, VGet( 0.0f, 0.0f, 0.0f ) );
	//	���f���̌����ݒ�
	MV1SetRotationXYZ( ground_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ), TO_RADIAN( 0.0f ) ) );
	//	���̐ݒ肳�ꂽ���W�ƌ����Ń��f���̕`��
	MV1DrawModel( ground_model );

	//	�m�o�b���f���̕`��
	for (int i = 0; i < MAX_ENEMY; i++)
	{
	MV1SetPosition( npc_model, VGet( npc_x[i], npc_y[i], npc_z[i]) );
	MV1SetRotationXYZ( npc_model, VGet( TO_RADIAN( 0.0f ), TO_RADIAN( 180.0f ), TO_RADIAN( 0.0f ) ) );
	MV1DrawModel( npc_model );
	}
	//	�x���ɂP�W�O�x��]�����ĉ�ʎ�O�������悤�ɂ��܂�

	//	�v���C���[���f���̕`��
	MV1SetPosition( player_model, VGet( player_x, player_y, player_z ) );
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( 0.0f  ), TO_RADIAN( 0.0f + player_rota), TO_RADIAN( 0.0f ) ) );
	MV1DrawModel( player_model );

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�v���C���[�ړ��ɍ��킹�Č������ύX", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�m�o�b�𕡐���", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "���@�������W�F�w�y���� -10.0f �` 10.0f", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	//	���f���f�[�^�̏I������
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
