#pragma once
#include "program/Main.h"

void PlayerControl()
{
	extern int playerx;
	extern int playery;
	extern double playerrotation;
	bool bRightKey = CheckHitKey(KEY_INPUT_RIGHT);
	bool bLeftKey = CheckHitKey(KEY_INPUT_LEFT);
	if (bRightKey)
	{
		int oob = SCREEN_W - 250;
		if (playerx <= oob)
		{
			playerx = playerx + 20;
			playerrotation = 0;
		}
	}
	else if (bLeftKey)
	{
		int oob = 0 -150;
		if (playerx >= oob)
		{
			playerx = playerx - 20;
			//playerx--;
			playerrotation = 3.14;
		}
	}
}