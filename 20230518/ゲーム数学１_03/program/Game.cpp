#include "Main.h"
#include "Game.h"
int posx;
int posy;

int posx2;
int posy2;

int count;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	posx = 400;
	posy = 225;
	posx2 = 225;
	posy2 = 225;
	count = 0;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------



void RandomizePos()
{
	posx = GetRand(SCREEN_W);
	posy = GetRand(SCREEN_H);
}

void GameUpdate()
{
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		RandomizePos();
	}

	if (PushHitKey(KEY_INPUT_RETURN))
	{
		int posrandomizer;
		posrandomizer = GetRand(10);
		if(posrandomizer == 1)
		{
		RandomizePos();
		}
	}


	count++;
	if (count >= 60)
	{
		count = 0;
		posx2 = GetRand(SCREEN_W);
		posy2 = GetRand(SCREEN_H);
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawCircle(posx, posy, 45, YELLOW, 1, 1);
	DrawCircle(posx2, posy2, 45, BLUE, 1, 1);
	//DrawCircle(0, 0, 45, GetColor(255,255,255), 1, 1);
	DrawString( 20, 20, "�X�y�[�X�F�~�̍��W�ݒ�i��ʓ��Ƀ����_���j", GetColor( 255, 255, 255 ) );
	
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}
