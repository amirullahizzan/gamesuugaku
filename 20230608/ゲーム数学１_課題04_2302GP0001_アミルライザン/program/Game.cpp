#include "Main.h"
#include "Game.h"

//	�m�o�b�̉摜�p�̕ϐ�
int npc_image;
//	�m�o�b�̍��W�p�̕ϐ�



int npc_x[5];	//	�w���W
int npc_y[5];	//	�x���W

//	�m�o�b���N���b�N�����񐔂����Ă����p�̕ϐ�
int click_count;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�m�o�b�摜�̓ǂݍ���
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�������W�̐ݒ�

	//	�N���b�N�񐔂O����J�n
	click_count = 0;

	for (int i = 0; i < 5; i++)
	{
		npc_x[i] = 100 + GetRand(500);
		npc_y[i] = GetRand(SCREEN_H - 50);
	}
}



void GameUpdate()
{
	int mouse_x = GetMouseX();
	int mouse_y = GetMouseY();
	//	�}�E�X���N���b�N�����Ƃ�

	for (int i = 0;i<5;i++)
	{
		npc_x[i] -= 2;


		if(npc_x[i] < 0)
		{
		npc_x[i] = SCREEN_W + 50;
		}

		if( PushMouseInput() )
		{
		//	�}�E�X���W�̎擾
	
		

		//	�����Ŏ擾�����}�E�X���W�i�_�j�Ƃm�o�b�i�l�p�j�Ŕ�������܂�
			if( mouse_x >= npc_x[i] && mouse_x <= npc_x[i] + 50 )
			{
			//	�c�����̔���
				if( mouse_y >= npc_y[i] && mouse_y <= npc_y[i] + 50 )
				{
				//	�������Ă�����m�o�b�̍��W�������_���Őݒ�
				npc_x[i] = SCREEN_W + GetRand(500);
				npc_y[i] = GetRand( SCREEN_H - 50 );

				//	�m�o�b���N���b�N�ł����̂ŃN���b�N�񐔂𑝂₵�܂�
				i--;
				click_count++;
				}
			}

		}



	}
	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�ǂݍ��񂾂m�o�b�摜�����W�ϐ��̏ꏊ�ɕ`��
	for (int j = 0; j < 5;j++)
	{

		DrawGraph(npc_x[j], npc_y[j], npc_image, TRUE);

	}

	//	�N���b�N���̕�������m�o�b������O�ɕ\���������̂łm�o�b�`��̌�ɋL�q���܂�
	DrawFormatString( 20, 80, GetColor( 255, 255, 255 ), "�m�o�b�N���b�N���F%d", click_count );

	DrawString( 20, 20, "�m�o�b��ʍ��Ɉړ��i���܂ōs������E����o�Ă���j", GetColor( 255, 255, 0 ) );
	DrawString( 20, 40, "�m�o�b�N���b�N�F�Ăщ�ʉE����o�Ă���", GetColor( 255, 255, 0 ) );

	DrawString( 20, 60, "�m�o�b����ʍ��ɍs������N���b�N�����Z�b�g", GetColor( 255, 255, 0 ) );
	
	DrawString( 20, 100, "�m�o�b�𕡐��\��", GetColor( 80, 210, 240 ) );
}


void GameExit()
{
	//	�ǂݍ��񂾂m�o�b�摜�̏I������
	DeleteGraph( npc_image );
}
