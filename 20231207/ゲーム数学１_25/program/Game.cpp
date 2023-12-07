#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�̔ԍ�������ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

#define NPC_MAX		5
Npc		npc[NPC_MAX];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�e���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	���ꂼ��̃N���X�̏������֐����Ă�
	//	�J�����̏�����
	camera.Init();
	//	���f���ԍ���n���Ă��ꂼ��̃N���X�̏�����
	ground.Init( ground_model );
	player.Init( player_model );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�N���X�̍X�V����
	ground.Update();
	player.Update();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}

	for (int i =0; i < NPC_MAX;i++)
	{
		if (CheckBoxHit3D(player.m_pos,player.m_size,npc[i].m_pos, npc[i].m_size))
		{
			//do smth
			npc[i].SetRandom();
		}
	}

	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�O�̘g�ɓ��������璵�˕Ԃ�悤�ȓ���", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "���@�v���C���[�Ƃm�o�b�œ����蔻��i����������m�o�b�̍��W�������_���ݒ�j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�X�y�[�X�F�W�����v", GetColor( 255, 255, 255 ) );

	DrawString( 16, 80, "�e�P�L�[�F�S�̃J����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "�e�Q�L�[�F�v���C���[�J����", GetColor( 255, 255, 255 ) );
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
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}
}
