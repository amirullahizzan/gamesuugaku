#pragma once
#include "program/Main.h"

void LoadBMP();


void LoadBMP()
{
	extern int player_image;
	extern int npc_image;
	player_image = LoadGraph("data/player.bmp");
	npc_image = LoadGraph("data/npc.bmp");
}