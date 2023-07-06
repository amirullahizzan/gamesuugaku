#include "Main.h"
#include "Game.h"

int player_image;
int player_x;
int player_y;


float speedmult;
int player_move;

void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100;
	player_y = 150;

	player_move = 0;
	speedmult = 1.1f;
}

void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )
	{
		player_x += 1*speedmult;
		speedmult+=0.1f;
	}
	else if (!CheckHitKey(KEY_INPUT_RIGHT))
	{
		speedmult = 0.1f;
	}

	if (player_x > SCREEN_W)
	{
		player_x = 0;
	}
	


}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawGraph( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "�E�L�[�@�F�E�ړ��i�X�s�[�h�����X�ɏグ�Ă����j", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�L�[�������Ă��Ȃ��Ƃ��̓X�s�[�h���O��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}
