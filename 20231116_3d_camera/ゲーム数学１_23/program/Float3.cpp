#include "Main.h"
#include "Game.h"
#include "Float3.h"

//---------------------------------------------------------------------------------
//	２点の長さを取得する関数
//---------------------------------------------------------------------------------
float GetFloat3Distance( Float3 pos1, Float3 pos2 )
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float z = pos1.z - pos2.z;
	float distance = sqrtf( x * x + y * y + z * z );
	return distance;
}
