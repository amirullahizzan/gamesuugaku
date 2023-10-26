#include "Main.h"
#include "Game.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	�Q�_�̒������擾����֐�
//---------------------------------------------------------------------------------
float GetFloat2Distance( Float2 pos1, Float2 pos2 )
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float distance = sqrtf( x * x + y * y );
	return distance;
}
