#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	//player_model = MV1LoadModel( "data/player.mqoz" );
	player_model = MV1LoadModel( "data/player2.mqoz" );
	//npc_model = MV1LoadModel( "data/npc.mqoz" );
	//MAGICA VOXEL SQUIDWARD
	npc_model = MV1LoadModel( "data/npc2.mqoz" );
	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	���E�L�[�ŉ�]�E��L�[�ňړ�
	player.Update();
	//	��]���Ă��邾��
	npc.Update();

	camera.Update();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�����ĕ`��J�n
	camera.Render();
	//	���f���̕`��
	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�����̃v���C���[���f���Ȃǂ̕\�������삵�����f���f�[�^�ɂ��Ă݂�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );

	camera.Exit();
	ground.Exit();
	player.Exit();
	npc.Exit();
}
