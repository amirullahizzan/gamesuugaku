#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOV_SPEED	5.0f
//	�v���C���[�̉�]�X�s�[�h�i�R�x�̃X�s�[�h�ŉ�]������j
#define PLAYER_ROT_SPEED	3.0f
//	�m�o�b�̈ړ��X�s�[�h
#define NPC_SPEED			1.0f
//	�v���C���[�Ƃm�o�b�̔��a�i�����傫���̉摜�Ȃ̂ŋ��ʂł��̒萔���g���Ă��܂��j
#define RADIUS				25.0f

#define MAX_ENEMY 20
//	�v���C���[�p�̕ϐ�
int player_image;		//	�摜
float player_x;			//	�w���W
float player_y;			//	�x���W
float player_rot;		//	�����i��]�p�x�F�x�j

//	�m�o�b�p�̕ϐ�
int npc_image;			//	�摜
float npc_x[MAX_ENEMY];			//	�w���W
float npc_y[MAX_ENEMY];			//	�x���W
float npc_rot[MAX_ENEMY];			//	�����i�x�j

void GameInit()
{
	//	�摜�̓ǂݍ��݁i�E�����̉摜�j
	player_image = LoadGraph( "data/player.bmp" );
	//	�������W�̐ݒ�
	player_x = 100.0f;
	player_y = 200.0f;
	//	�v���C���[�摜�̏��������i�O�x����n�߂�j
	player_rot = 0.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		npc_x[i] = 500.0f;
		npc_y[i] = 300.0f;
		//npc_rot[i] = GetRand(360);
		npc_rot[i] = (360.0f/MAX_ENEMY)*i;
	}
	//	�m�o�b�͏����ݒ�Ń����_���Ȍ�����
}

void GameUpdate()
{
	//	���E�L�[�ŉ�]
	//	�E�L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	�摜���E��]���������i�p�x�I�ɂ̓v���X�����j
		player_rot += PLAYER_ROT_SPEED;
	}
	//	���L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//	�摜������]���������i�p�x�I�ɂ̓}�C�i�X�����j
		player_rot -= PLAYER_ROT_SPEED;
	}

	//	��L�[�Ō����Ă�������Ɉړ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	player_rot �̕����� PLAYER_MOV_SPEED �����W�ړ�
		player_x += PLAYER_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		player_y += PLAYER_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
	}

	//	�m�o�b�̍��W�ړ��i�����Ă�������Ɉړ��j


	//	��ʂ̊O�ɍs�����甽�΂���o�Ă���


	//	�v���C���[�Ƃm�o�b�œ����蔻��
	for (int i = 0 ; i < MAX_ENEMY ;i++)
	{
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x[i], npc_y[i], RADIUS))
	{
		//	�������Ă�����m�o�b�̍��W�ƌ����������_���ɍĐݒ�
		npc_x[i] = GetRand(SCREEN_W - RADIUS) + RADIUS;
		npc_y[i] = GetRand(SCREEN_H - RADIUS) + RADIUS;
		npc_rot[i] = GetRand(360);
	}
	//BOUNDARY
	if (npc_x[i] < 0)
	{
		npc_x[i] = SCREEN_W;
	}
	if (npc_y[i] < 0)
	{
		npc_y[i] = SCREEN_H;
	}
	if (npc_x[i] > SCREEN_W)
	{
		npc_x[i] = 0;
	}
	if (npc_y[i] > SCREEN_H)
	{
		npc_y[i] = 0;
	}

	npc_x[i] += cosf(TO_RADIAN(npc_rot[i])) * NPC_SPEED;
	npc_y[i] += sinf(TO_RADIAN(npc_rot[i])) * NPC_SPEED;
	}

	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̍��W�ƌ�����n���ĕ`��
	for (int i = 0 ;i < MAX_ENEMY; i++)
	{
	DrawRotaGraphF( npc_x[i], npc_y[i], 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	//	���W�ƌ�����n���ĉ摜��`��i player_rot�F�x�����W�A���ɕϊ����Ċ֐��ɓn���Ă��܂��j
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20,  20, "�����L�[�F�v���C���[��]", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�L�[�F�v���C���[�̌����Ă�������Ɉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "�m�o�b�͏����ݒ�Ń����_���Ȍ�����", GetColor( 255, 255, 0 ) );
	DrawString( 20,  80, "�m�o�b�������Ă�������Ɉړ�", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "�m�o�b�̓v���C���[�Ɠ�����ƍ��W�ƌ������Đݒ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
