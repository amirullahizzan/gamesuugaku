#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include <vector>

#define PLAYER_MOV_SPEED	5.0f
#define PLAYER_ROT_SPEED	3.0f
#define MISSILE_SPEED		10.0f

int player_image;
float player_x;
float player_y;
float player_rot;

int missile_image;
//float missile_x;
//float missile_y;
enum {
	MODE_WAIT,
	MODE_MOVE,
};
class Missile
{
private :
	bool OOBHandler()
	{
		if (x < 0){return true;	}
		else if (x > SCREEN_W){return true;	}
		else if (y < 0){return true;	}
		else if (y > SCREEN_H){return true;	}
		else
		{
			return false;
		}
	}
	

public :
	float x = 0;
	float y = 0;
	int mode = MODE_WAIT;
	float rot = 0.0f;
	int spawnduration = 200;
	Missile()
	{
		x = player_x;
		y = player_y;
		rot = player_rot;
		if (mode == MODE_WAIT)
		{
		mode = MODE_MOVE;
		}
	};

	void Move()
	{
		if (mode == MODE_MOVE)
		{
			x += MISSILE_SPEED * (cosf(TO_RADIAN(rot)));
			y += MISSILE_SPEED * (sinf(TO_RADIAN(rot)));
			if (OOBHandler())
			{
				mode = MODE_WAIT;
			}
		}
	}

	void Despawner(std::vector<Missile>& missile)
	{
		if (spawnduration > 0) spawnduration--;
		if (spawnduration <= 0 && OOBHandler())
		{
			for (auto it = missile.begin(); it != missile.end(); ++it)
			{
				if (&(*it) == this)
				{
					missile.erase(it);
					break; // Exit the loop after erasing
				}
			}
		}
	}
};
std::vector<Missile> missile;


void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;
	player_rot = 0.0f;

	missile_image = LoadGraph( "data/missile.bmp" );
}

void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_rot += PLAYER_ROT_SPEED;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_rot -= PLAYER_ROT_SPEED;
	}

	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_x += PLAYER_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		player_y += PLAYER_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		missile.push_back(Missile());
	}

	for (int i = 0;i < missile.size();i++)
	{
		missile[i].Move();
		missile[i].Despawner(missile);
	}

	//missile.Move

}

void GameRender()
{
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	for (int i = 0;i < missile.size();i++)
	{
		DrawRotaGraphF(missile[i].x, missile[i].y, 1.0f, TO_RADIAN(missile[i].rot), missile_image, TRUE);
	}

	DrawString( 20, 20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "スペース：ミサイル発射", GetColor( 255, 255, 255 ) );
}

void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( missile_image );
}
