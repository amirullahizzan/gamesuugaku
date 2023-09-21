#include "Main.h"
#include "Game.h"

#define PLAYER_MOV_SPEED	5.0f
#define PLAYER_ROT_SPEED	3.0f

#define LENGTH_NEAR		50.0f
#define LENGTH_FAR		100.0f
#define OPTION_MAX		4

int player_image;
float player_x;
float player_y;
float player_rot;

int option_image;
float option_x[OPTION_MAX];
float option_y[OPTION_MAX];
float option_rot[OPTION_MAX];

//class Minion
//{
//public :
//	float x = 0;
//	float y = 0;
//	float rot = 0;
//};



//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//Minion minion1 = {0,0,0};

	player_image = LoadGraph( "data/player.bmp" );
	option_image = LoadGraph( "data/option.bmp" );

	player_x = 100.0f;
	player_y = 200.0f;
	player_rot = 0.0f;

	for (int i = 0;i<OPTION_MAX;i++)
	{
	option_x[i] = 100.0f;
	option_y[i] = 300.0f;
	option_rot[i] = 0.0f;
	}

}


void GameUpdate()
{
	
	if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player_rot += PLAYER_ROT_SPEED;
		/*option_x -= 5.2 *GetLength_RotSotte(TO_RADIAN(player_rot));
		option_y -= 5.2* GetLength_RotMukai(TO_RADIAN(player_rot));*/
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_rot -= PLAYER_ROT_SPEED;
	}

	if( CheckHitKey( KEY_INPUT_UP ) ){
		float mov_x = PLAYER_MOV_SPEED * GetLength_RotSotte(TO_RADIAN(player_rot));
		float mov_y = PLAYER_MOV_SPEED * GetLength_RotMukai(TO_RADIAN(player_rot));
		player_x += mov_x;
		player_y += mov_y;
	}
	float sidemult = LENGTH_NEAR;

	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		sidemult = LENGTH_FAR;
	}

	/*float mov_x = LENGTH_NEAR * GetLength_RotSotte(TO_RADIAN(player_rot));
	float mov_y = LENGTH_NEAR * GetLength_RotMukai(TO_RADIAN(player_rot));*/
	for (int i = 0; i < OPTION_MAX; i++)
	{
	float mov_x = sidemult * GetLength_RotSotte(TO_RADIAN(player_rot + (360/OPTION_MAX * i) ));
	float mov_y = sidemult * GetLength_RotMukai(TO_RADIAN(player_rot + (360 / OPTION_MAX * i) ));
	option_x[i] = player_x;
	option_y[i] = player_y;
	option_rot[i] = player_rot+90*i;
	option_x[i] = player_x + mov_x;
	option_y[i] = player_y + mov_y;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawCircle(player_x, player_y,50,GetColor(255,255,0),false,1);
	DrawCircle(player_x, player_y,100,GetColor(255,255,0),false,1);
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	for (int i = 0;i<OPTION_MAX;i++)
	{
	DrawRotaGraphF( option_x[i], option_y[i], 1.0f, TO_RADIAN(option_rot[i]), option_image, TRUE);
	}

	DrawString( 20, 20, "←→キー：プレイヤー回転", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "↑　キー：プレイヤーの向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "オプションをプレイヤーの前後左右に", GetColor( 255, 255, 255 ) );
	DrawString( 20, 80, "左シフトキー：オプションの距離を遠くに", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}
