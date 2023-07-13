#include "Main.h"
#include "Game.h"

#define RADIUS		50.0f

float pos_x;
float pos_y;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
float GetDistance( float x1, float y1, float x2, float y2 )
{
	float x = x1 - x2;
	float y = y1 - y2;

	float d = sqrtf( x * x + y * y );
	// Circle euclidean distance func

	return d;
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	pos_x = 100.0f;
	pos_y = -50.0f;
}

int color = GetColor(128, 128, 128);


bool ismouseOver = false;
void GameUpdate()
{
	float mouse_x = (float)GetMouseX();
	float mouse_y = (float)GetMouseY();

	/*if (mouse_x > pos_x -50 && mouse_x < pos_x + 50)
	{
		if(mouse_y > pos_y - 50 && mouse_y < pos_y + 50) 
		{
		ismouseOver = true;
		}
	}*/ //for SQUARE

	pos_y+=2;

	if (GetDistance(pos_x,pos_y,mouse_x,mouse_y) < RADIUS)
	{
		ismouseOver = true;
		if (GetMouseInput())
		{
			color = GetColor(128, 128, 255);
		}
	}
	else
	{
		ismouseOver = false;
	}

	if (pos_y > SCREEN_H+RADIUS)
	{
		pos_y = 0 - RADIUS;
		color = GetColor(128, 128, 128);
	}

}



void GameRender()
{
	DrawCircle( pos_x, pos_y, RADIUS, color );


	if (ismouseOver)
	{
		DrawString(20, 80, "円の中にマウス座標が入っています", GetColor(200, 200, 50));
	}

	DrawString( 20,  20, "マウスで円をクリック", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "→　クリックされたら色の変更", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "→　画面下まで行ったら色を戻して画面の上に", GetColor( 255, 255, 255 ) );
}



void GameExit()
{

}
