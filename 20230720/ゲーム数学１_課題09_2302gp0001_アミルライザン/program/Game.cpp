#include "Main.h"
#include "Game.h"
//	CheckCircleHit �̊֐����g�������̂ŁA���̖��O�������Ă���w�b�_�[�t�@�C�����C���N���[�h���܂�
#include "Hit.h"

//	�m�o�b�̐�
#define NPC_MAX		10

//	�m�o�b�~�̔��a
#define NPC_RADIUS		25.0f
//	�~�T�C���~�̔��a
#define MISSILE_RADIUS	10.0f

//	�~�T�C�����W
float missile_x;
float missile_y;
//	�~�T�C�����ǂ�ȏ�Ԃ��i�O�F�㉺�ړ�����@�P�F�E�Ɉړ��j
int missile_mode;

//	�m�o�b���W
float npc_x[NPC_MAX];
float npc_y[NPC_MAX];

float explosion_radius;
float explosion_x;
float explosion_y;
bool isExploding = false;
bool isMissileExist = true;


//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�~�T�C���������W
	missile_x = 50.0f;
	missile_y = SCREEN_H / 2.0f;
	//	�~�T�C���͍ŏ��͏㉺�ړ��������Ԃ���J�n
	missile_mode = 0;

	//	�m�o�b�������W
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc_x[i] = (float)GetRand(SCREEN_W) + SCREEN_W;
		npc_y[i] = (float)GetRand(SCREEN_H - NPC_RADIUS)+NPC_RADIUS;
	}

	explosion_x = 0;
	explosion_y = 0;
	explosion_radius = 0;
}

void ResetNpc(int i)
{
		npc_x[i] = (float)GetRand(SCREEN_W + NPC_RADIUS)+SCREEN_W;
		npc_y[i] = (float)GetRand(SCREEN_H-NPC_RADIUS)+ NPC_RADIUS;
}

void MoveExplosion(int x, int y)
{
	explosion_x = x;
	explosion_y = y;
}

void ResetExplosion()
{
	explosion_x = 0;
	explosion_y = 0;
	explosion_radius = 0;
	isExploding = false;
}


void DestroyMissile()
{
		
		isMissileExist = false;
}

int score = 0;

void ResetMissile()
{
	missile_x = 50.0f;
	missile_y = SCREEN_H / 2.0f;
	missile_mode = 0;
	isMissileExist = true;
}

void SpawnExplosion()
{
	explosion_radius+=6;
	
	for (int i = 0; i < NPC_MAX; i++)
	{
		if (CheckCircleHit(explosion_x, explosion_y, explosion_radius, npc_x[i], npc_y[i], NPC_RADIUS))
		{
			ResetNpc(i);
			score++;
		}
	}
	
	if (explosion_radius >= 200.0f)
	{
		ResetExplosion();
		ResetMissile();
	}
}


void GameUpdate()
{
	//	�㉺�ړ����������Ԃ̎�
	if( missile_mode == 0 ){
		//	�㉺�L�[�ŏ㉺�̍��W�ړ�
		if( CheckHitKey( KEY_INPUT_DOWN ) )		missile_y += 3.0f;
		if( CheckHitKey( KEY_INPUT_UP ) )		missile_y -= 3.0f;
		//	�X�y�[�X�L�[����������
		if( PushHitKey( KEY_INPUT_SPACE ) ){
			//	�E�Ɉړ��������Ԃɂ������̂�
			missile_mode = 1;
		}
	}
	//	���ł����Ԃ̎�
	if( missile_mode == 1 ){
		//	��ʉE�Ɉړ�
		missile_x += 10.0f;
		//	��ʂ̉E�܂ōs������
		if( missile_x > SCREEN_W + MISSILE_RADIUS ){
			//	�㉺�L�[�ňړ������Ԃɖ߂��܂�
			missile_mode = 0;
			//	���W���������W�ɖ߂��܂�
			missile_x = 50.0f;
			missile_y = SCREEN_H / 2.0f;
		}
	}

	//	��ʍ��Ɉړ�
	for (int i = 0; i < NPC_MAX; i++)
	{
		npc_x[i] -= 3.0f;
		//	��ʍ��܂ōs������i�~���S���B���܂Łj
		if (npc_x[i] < -NPC_RADIUS)
		{
			ResetNpc(i);
		}
	}

	for (int i = 0; i < NPC_MAX; i++)
	{
		bool check = CheckCircleHit(missile_x, missile_y, MISSILE_RADIUS, npc_x[i], npc_y[i], NPC_RADIUS);
	

	if( check == true && isExploding == false){
		//	�m�o�b�̍��W���Đݒ�
		MoveExplosion(missile_x, missile_y);
		isExploding = true;
		
			npc_x[i] = SCREEN_W + NPC_RADIUS;
			npc_y[i] = (float)GetRand(SCREEN_H);

		//	�~�T�C�����㉺�ړ��������Ԃɖ߂��܂�
			DestroyMissile();
	}
	}

	if (isExploding)
	{
		SpawnExplosion();
	}
}



void GameRender()
{
	//	�m�o�b���W�Ɣ��a��n���ĉ~�̕`��
	DrawCircle(explosion_x, explosion_y, explosion_radius, GetColor(150,255,120) ,0,1 );

	for (int i = 0; i < NPC_MAX; i++)
	{
		DrawCircle(npc_x[i], npc_y[i], NPC_RADIUS, GetColor(255, 128, 128));
	}
	//	�~�T�C����
	if (isMissileExist)
	{
		DrawCircle(missile_x, missile_y, MISSILE_RADIUS, GetColor(128, 255, 128));
	}

	DrawString( 20,  20, "�㉺�L�[�F�ΐF�̃~�T�C���~�̏㉺�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "�X�y�[�X�F�~�T�C���~�̉��ړ��J�n", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "�Ԃ��m�o�b�~�ƃ~�T�C���~��������Ƃm�o�b�͍��W�Đݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "�m�o�b�𕡐��ɂ���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "�~�T�C�����m�o�b�Ɠ���������~�T�C���͂��̏ꏊ�ōL�����Ă���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 120, "���@�L�����Ă���Ƃ��̃~�T�C���~�̕`��͘g�����ɂ���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 140, "���@������x�傫���Ȃ�����J�n�ʒu�ɖ߂�", GetColor( 255, 255, 0 ) );
	DrawFormatString( 20, 300, GetColor(255, 255, 0) , "Enemy Destroyed : %02d ",  score);

}


void GameExit()
{
}
