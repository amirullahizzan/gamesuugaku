#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"

//#define COUNT_MAX		10
#define COUNT_MAX		15

#define ADD_POINT		100

#define BAR_W			500
#define BAR_H			15

int icon_image;

int push_count;

int game_point;

int draw_point;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	icon_image = LoadGraph( "data/icon.bmp" );

	push_count = 0;

	game_point = push_count * ADD_POINT;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	if( PushHitKey( KEY_INPUT_UP ) ){
		push_count++;

		if( push_count >= COUNT_MAX ){
			push_count = COUNT_MAX;
		}

		game_point = push_count * ADD_POINT;
	}

	if (draw_point < game_point)
	{
		draw_point += 3;
		if (draw_point > game_point)
		{
			draw_point = game_point;
		}
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//ICON
	for (int i = 0; i < push_count; i++)
	{
		int pos_x = 100 + 20 * (i % 5);
		int pos_y = 240 + 20 * (i / 5);
		DrawRotaGraph(pos_x, pos_y, 1, 0, icon_image, 1);
	}


	int barcolor[3];
	{
		barcolor[0] = GetColor(255, 125, 125);
		barcolor[1] = GetColor(125, 255, 125);
		barcolor[2] = GetColor(125, 125, 255);
	}
	int barcount = game_point / BAR_W;
	int barpoint = game_point % BAR_W;
	
	if (barcount > 0)
	{
		//previous bar
		DrawFillBox(100, 100, 100 + BAR_W, 100 + BAR_H, barcolor[barcount -1]);
	}
	if (barpoint > 0)
	{
		//current bar
		DrawFillBox(100, 100, 100+barpoint, 100 + BAR_H, barcolor[barcount]);
	}

	/*if (barpoint > 0)
	{
	DrawFillBox(100,100,100+game_point%500,100+BAR_H, barcolor[1]);
	}*/
	DrawLineBox( 100, 100, 100 + BAR_W, 100 + BAR_H, GetColor( 255, 255, 255 ) );

	DrawFormatString(20, 180, GetColor(0, 255, 0), "�\���|�C���g�F%d", draw_point);
	barcount = draw_point / BAR_W;
	barpoint = draw_point % BAR_W;

	if (barcount > 0)
	{
		//previous bar
	DrawFillBox(100, 200, 100 + BAR_W, 200 + BAR_H, barcolor[barcount-1]);
	}
	if (barpoint > 0)
	{
		//current bar
	DrawFillBox(100,200,100 + barpoint,200+BAR_H, barcolor[barcount]);
	}

	DrawLineBox( 100, 200, 100 + BAR_W, 200 + BAR_H, GetColor( 255, 255, 255 ) );


	DrawString( 20, 280, "�������񐔂ɍ��킹�ăA�C�R������ׂ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 20, "��L�[�F�������񐔂𑝂₷�i�P�O�܂Łj", GetColor( 255, 255, 255 ) );
	DrawFormatString( 20, 40, GetColor( 255, 255, 0 ), "�������񐔁F%d", push_count );
	DrawFormatString(20, 80, GetColor(0, 255, 255), "�Q�[���|�C���g�i��������x100�j�F%d", game_point);

	
	
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( icon_image );
}
