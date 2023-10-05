#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	3.0f
//	����͖ڕW�̍��W�Ɍ������ς��̂ŉ�]�X�s�[�h�͂���܂���

//	�m�o�b�̈ړ��X�s�[�h�i�����x�߂ɂ��Ă��܂��j

//	�����蔻��Ŏg���̂Ńv���C���[�Ƃm�o�b�̔��a
#define CHARA_RADIUS	25.0f
//	�~�̔��a
#define CIRCLE_RADIUS	50.0f
//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
float player_x;		//	�w���W
float player_y;		//	�x���W
float player_rot;	//	�����i�x�F�ڕW���W�Ɍ����悤�ɂ��܂��j
//	�m�o�b�p�̕ϐ�
int npc_image;
int npctarget[5];

const int MAX_NPC = 5;
float NPC_SPEED[MAX_NPC];
float npc_x[MAX_NPC];
float npc_y[MAX_NPC];
float npc_rot[MAX_NPC];

//	�~
float circle_x;			//	�w���W
float circle_y;			//	�x���W

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_x = 150.0f;
	player_y = 200.0f;
	//	�ŏ��͂O�x�i�E�����j�ŊJ�n
	player_rot = 0.0f;

	for (int i = 0; i < MAX_NPC; i++)
	{
		npctarget[i] = 0;
		npc_x[i] = (float)GetRand(500.0f);
		npc_y[i] = (float)GetRand(300.0f);
		npc_rot[i] = 0.0f;
		NPC_SPEED[i] = GetRand(5)+ 2;
	}

	circle_x = 700.0f;
	circle_y = 0.0f;
}

float px = 0;
float py = 0;
float nx = 0;
float ny = 0;

enum PlayerTargetEnum
{
	ToNPC = 0, ToBall = 1
};

void GameUpdate()
{
	//	�v���C���[���}�E�X�̕��Ɍ����킹��
	//	�P�F�ڕW���W�i�}�E�X���W�j���擾
	float mouse_x = GetMouseX();
	float mouse_y = GetMouseY();
	//	�Q�F���̍��W�i�v���C���[���W�j����ڕW���W�i�}�E�X���W�j�܂łǂ̂��炢��

	px = mouse_x - player_x;
	py = mouse_y - player_y;
	//	�R�F���̒l���g���Ċp�x�����߂�i GetRadian_LengthYX�Fy x ��n���ƃ��W�A���p�����炦��֐��j
	float radian = GetRadian_LengthYX( py, px );
	//	��Ŏ擾�����p�x�̓��W�A���p�Ȃ̂ŁA���̊p�x���u�x�v�ɂ��ăv���C���[�̊p�x�ϐ��ɓn���܂�
	//	TO_DEGREE�F���W�A���p���u�x�v�ɕϊ�����֐�
	player_rot = TO_DEGREE( radian );

	//	���̂܂܂��ƃv���C���[���}�E�X���W�̂Ƃ�����s�����藈������J��Ԃ��Ă��܂��̂�
	//	�v���C���[���}�E�X�ɂ������Ă��Ȃ��Ƃ������ړ�����悤�ɂ��܂�
	if( CheckPointCircleHit( mouse_x, mouse_y, player_x, player_y, CHARA_RADIUS ) == false ){
		//	�S�F�v���C���[�̌��������܂����̂ł��̕����ɍ��W�ړ������܂�
		//	PLAYER_SPEED ���v���C���[�̌����ɍ��킹�Ăw�����Ƃx�����ɕ����܂�
		//	���̕����W�ړ������܂�
		float mov_x = PLAYER_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		float mov_y = PLAYER_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
		if (player_x > SCREEN_W/2)
		{
			player_x = SCREEN_W/2;
		}
		player_x += mov_x;
		player_y += mov_y;
	}

	//	�~�̈ړ�
	circle_y += 1.0f;
	if( circle_y > SCREEN_H ){
		circle_y = 0.0f;
	}
	
	for (int i = 0; i < MAX_NPC; i++)
	{
		switch (npctarget[i])
		{
		case ToNPC:
			nx = player_x - npc_x[i];
			ny = player_y - npc_y[i];
			if (CheckCircleHit(player_x, player_y, CHARA_RADIUS, npc_x[i], npc_y[i], CHARA_RADIUS))
			{
				NPC_SPEED[i] = GetRand(5) + 2;
				npctarget[i] = ToBall;
			}
			break;
		case ToBall:
			nx = circle_x - npc_x[i];
			ny = circle_y - npc_y[i];
			if (CheckCircleHit(npc_x[i], npc_y[i], CHARA_RADIUS, circle_x, circle_y, CIRCLE_RADIUS))
			{
				NPC_SPEED[i] = GetRand(5) + 2;
				npctarget[i] = ToNPC;
			}
			break;
		}

		//	�m�o�b�̓v���C���[�Ɍ������Ĉړ�����
		//	�m�o�b���猩�ăv���C���[���ǂꂾ���i�񂾐�ɂ��邩
		//	���̒l���g���Ċp�x�����߂�i GetRadian_LengthYX ����擾�������W�A���p���u�x�v�ɕϊ����� npc_rot �ɓn���܂��j
		npc_rot[i] = TO_DEGREE(GetRadian_LengthYX(ny, nx));
		//	�m�o�b�̌��������܂����̂ł��̕����Ɉړ������܂��i�ړ��ʂ����߂Ă�������W�ɑ����܂��j
		npc_x[i] += NPC_SPEED[i] * GetLength_RotSotte(TO_RADIAN(npc_rot[i]));
		npc_y[i] += NPC_SPEED[i] * GetLength_RotMukai(TO_RADIAN(npc_rot[i]));
	}
	//	�v���C���[�Ƃm�o�b�̓����蔻��i�~���m�Łj

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("player x : %f",player_x);
	//	�v���C���[�ړ��͈͂̕`��
	DrawFillBox( 0, 0, SCREEN_W / 2, SCREEN_H, GetColor( 0, 64, 128 ) );
	//	�~�̕`��
	DrawCircleAA( circle_x, circle_y, CIRCLE_RADIUS, 30, GetColor( 255, 255, 255 ) );

	for (int i = 0;i < MAX_NPC;i++)
	{
	DrawRotaGraphF( npc_x[i], npc_y[i], 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 16, 16, "�v���C���[�F�}�E�X�Ɍ������Ĉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�ړ��͈͉͂�ʍ����i�E�̉~�Ƌ�������肽���̂Łj", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�m�o�b�@�@�F�v���C���[�Ɍ������Ĉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "���@�v���C���[�ɓ���������~�Ɍ�����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "���@�~�ɓ���������v���C���[�Ɍ�����", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "���@�����邽�тɌ��������؂�ւ���", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
