#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	�L�����̔��a
#define CHARA_RADIUS	0.5f
//	�m�o�b�̐�
#define NPC_MAX		8

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
Npc		npc[NPC_MAX];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	�N���X�̏������i�g�����f���f�[�^��n���āj
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );

	for (int i = 0; i < NPC_MAX;i++)
	{
	npc[i].Init( npc_model );
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	���E�L�[�ŉ�]�E��L�[�ňړ�
	player.Update();
	//	��]���邾��

	for (int i = 0; i < NPC_MAX;i++)
	{

		npc[i].Update();
		//	���ꂼ��̍��W�̍X�V���I���܂����̂ŋ����m�œ����蔻������܂�
		if (CheckBallHit(player.m_pos, CHARA_RADIUS, npc[i].m_pos, CHARA_RADIUS)) {
			//	�m�o�b�̍��W�������_���Ɂi���_����n�ʂ̎l�p�v���X�}�C�i�X�P���j
			npc[i].m_pos.x = GetRandomF(-10.0f, 10.0f);
			npc[i].m_pos.z = GetRandomF(-10.0f, 10.0f);

			npc[i].ScaleModel(1.1f);
		}

	}
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
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "�����L�[�F�v���C���[��]", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�v���C���[�Ƃm�o�b�œ����蔻��@���@����������m�o�b�̍��W�������_���ɐݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�m�o�b�𕡐��ɂ���", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "�m�o�b�������Ă�������Ɉړ�������", GetColor( 255, 255, 0 ) );
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
	
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Exit();
	}
}
