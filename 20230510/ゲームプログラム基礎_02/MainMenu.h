#pragma once
#include "program/Game.h"

int title_bmp;
int bg_bmp;

void MoveTitle();
void InitImage();
void DisplayTitle();

int x = SCREEN_W / 8;
int y = -100;

void InitImage()
{
	title_bmp = LoadGraph("data/title.bmp", TRUE);
	bg_bmp = LoadGraph("data/bg.bmp", TRUE);
}

void MoveTitle()
{
	if (y < SCREEN_H / 4)
	{
		y += 2;
	}
}
void DisplayTitle()
{
	DrawGraph(0, 0, bg_bmp, FALSE);
	DrawGraph(x, y, title_bmp, TRUE);
}

