#include "Main.h"
#include "Game.h"

//	�~�̍ő吔
#define CIRCLE_MAX	5

//	�~�̔��a�i����͔��a�̑傫���͕ς��Ȃ��̂Łj
#define RADIUS		50.0f
//	�~�̂w���W
float pos_x[CIRCLE_MAX];
//	�~�̂x���W
float pos_y[CIRCLE_MAX];
//	�~���N���b�N�������ǂ����̕ϐ��i�O�F�N���b�N���Ă��Ȃ��@�P�F�N���b�N�����j
int click[CIRCLE_MAX];

//	�~�̍��W�ƃ}�E�X���W�̋���������p�̕ϐ�
float distance[CIRCLE_MAX];

//---------------------------------------------------------------------------------
//	�Q�_�̋�����Ԃ��֐�
//		x1 y1�F�P�_�ڂ̍��W
//		x2 y2�F�Q�_�ڂ̍��W
//	�Q�_�̋�����Ԃ��܂��i float �^�̒l�ł��j
//---------------------------------------------------------------------------------
float GetDistance( float x1, float y1, float x2, float y2 )
{
	//	�w�����̍�
	float x = x1 - x2;
	//	�x�����̍�
	float y = y1 - y2;
	//	��ŋ��߂��w�����Ƃx�����̍�����Q�_�Ԃ̋��������߂�
	//	sqrtf�F�󂯎�����l�����[�g����֐�
	float d = sqrtf( x * x + y * y );
	//	���̋�����Ԃ�
	return d;
}
int speed[CIRCLE_MAX];
int color[CIRCLE_MAX];


bool Done[5];

void GameInit()
{
	//	�Ƃ肠�����~�̏������W�i��ʂ̏ォ��J�n�j
	for (int i = 0;i< CIRCLE_MAX;i++)
	{
		pos_x[i] = 100 + (100 * i) ;
		pos_y[i] = -RADIUS;
		speed[i] = GetRand(20);
		color[i] = GetColor(128, 128, 128);
		Done[i] = false;
		click[i] = 0;
	}
	
	//	�N���b�N���Ă��Ȃ���Ԃ���J�n
}

void GameUpdate()
{
	//	�~�̈ړ�
	int ballOutCount = 0;

	float mouse_x = (float)GetMouseX();
	float mouse_y = (float)GetMouseY();

	for (int i = 0;i< CIRCLE_MAX;i++)
	{

		pos_y[i] += (speed[i]/10.0f)+1.0f;
		if (pos_y[i] > SCREEN_H + RADIUS) 
		{
			//	��ʂ̏ォ��i�~�����ׂĉB��Ă����Ԃ���J�n�������j
			//	��ʂ̏ォ��o�Ă���^�C�~���O�ŃN���b�N��Ԃ���������
			ballOutCount++;

			
			
		}

	
			distance[i] = GetDistance(pos_x[i], pos_y[i], mouse_x, mouse_y);

			if (PushMouseInput()) 
			{
				//	�~�̒��Ƀ}�E�X���W�������Ă�����i�Q�_�̋����Ɣ��a�̔�r�j
				if (distance[i] <= RADIUS) {
					//	�~���N���b�N�ł����̂�
					click[i] = 1;
				}
			}

	}

	if (ballOutCount == CIRCLE_MAX)
	{
		for (int i = 0; i < CIRCLE_MAX; i++)
		{
			pos_y[i] = -RADIUS;
			click[i] = 0;
			speed[i] = (float)GetRand(20);
			color[i] = GetColor(128, 128, 128);
		}

	}

}


void GameRender()
{
	//	�D�F�Łi�N���b�N������F��ς��悤�Ǝv���܂��j
	//	�N���b�N����Ă���̂ł����
	
	//	���̐F�ŉ~�̕`��

	for (int i = 0;i< CIRCLE_MAX;i++)
	{
		DrawCircle(pos_x[i], pos_y[i], RADIUS, color[i]);
		if (click[i] == 1)
		{
			//	�F��ύX����
			color[i] = GetColor(128, 128, 255);
		}
	}

	DrawString( 20,  20, "�}�E�X�ŉ~���N���b�N", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�N���b�N���ꂽ��F�̕ύX", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "���@��ʉ��܂ōs������F��߂��ĉ�ʂ̏��", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "�~�𕡐��ɂ��ĕ��ׂ�", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "�~�� 1.0 �` 3.0 �̃����_���ȃX�s�[�h�ŉ�ʉ��Ɉړ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}
