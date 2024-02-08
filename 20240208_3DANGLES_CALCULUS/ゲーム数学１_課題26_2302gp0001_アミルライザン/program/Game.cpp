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
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	//	�N���X�̏�����
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc[i].Init(npc_model);
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------

void RandomizePos(Float3 &pos, Float3 &rot)
{
	int randSpot = GetRand(4);
	float corner_rotation_mult = 90.0f;
	switch (randSpot)
	{
	case 0:
		pos.z = 10.0f; pos.x = -10.0f;
		rot.y = GetRandomF(corner_rotation_mult*1, corner_rotation_mult*2);
		break;

	case 1:
		pos.z = 10.0f; pos.x = 10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 2, corner_rotation_mult * 3);
		break;

	case 2:
		pos.z = -10.0f; pos.x = -10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 4, corner_rotation_mult * 5);
		break;

	case 3:
		pos.z = -10.0f; pos.x = 10.0f;
		rot.y = GetRandomF(corner_rotation_mult * 3, corner_rotation_mult * 4);
		break;
	}
}
void GameUpdate()
{
	ground.Update();
	//	���E�L�[�ŉ�]�E��L�[�ňړ�
	player.Update();

	//	�v���C���[�̕��ɏ��X�Ɍ�����ς��Ȃ���ړ�����i�Ȃ̂Ńv���C���[���W��n���܂��j
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc[i].Update(player.m_pos);

		//	���ꂼ��̍��W�̍X�V���I���܂����̂ŋ����m�œ����蔻������܂�
		if (CheckBallHit(player.m_pos, CHARA_RADIUS, npc[i].m_pos, CHARA_RADIUS)) {
			//	�m�o�b�̍��W�������_���Ɂi���_����n�ʂ̎l�p�v���X�}�C�i�X�P���j
			//npc[i].m_pos.z = GetRandomF(-10.0f, 10.0f);
			//npc[i].m_pos.x = GetRandomF(-10.0f, 10.0f);
			//npc[i].m_rot.y = GetRandomF(0.0f, 360.0f);

			RandomizePos(npc[i].m_pos,npc[i].m_rot);
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

	DrawString(16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor(255, 255, 255));
	DrawString(16, 32, "�m�o�b�̓v���C���[�̕��Ɍ�����ς��Ȃ���ړ�", GetColor(255, 255, 255));
	DrawString(16, 48, "�v���C���[�Ƃm�o�b�œ����蔻��@���@����������m�o�b�̍��W�������_���ɐݒ�", GetColor(255, 255, 255));
	DrawString(16, 64, "�m�o�b�𕡐��ɂ���i���������������_���Ɂj", GetColor(255, 255, 0));
	DrawString(16, 80, "�m�o�b�Đݒ���W�͉��F���̈�́u�����E����E�E��E�E���v�̂ǂꂩ", GetColor(255, 255, 0));
	DrawString(16, 96, "���@���������̓o��ꏊ���物�F���̈���Ɍ������ă����_���Ȍ�����", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
	MV1DeleteModel(npc_model);

	camera.Exit();
	ground.Exit();
	player.Exit();
	for (int i = 0; i < NPC_MAX; i++)
	{
	npc[i].Exit();
	}
}
