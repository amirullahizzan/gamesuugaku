#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"
#include "BG.h"

//	�f�[�^�p�̕ϐ�
int bg_image;		//	�w�i�p
int player_image;	//	�v���C���[
int npc_image;		//	�m�o�b

//	�N���X�̐錾
BG		bg;			//	�w�i
Player	player;		//	�v���C���[
Npc		npc;		//	�m�o�b

float camera_x = 0;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�f�[�^�̓ǂݍ���
	bg_image = LoadGraph( "data/bg.bmp" ); //3000 x 450
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�ǂݍ��񂾃f�[�^��n���ď�����
	bg.Init( bg_image );
	player.Init( player_image );
	npc.Init( npc_image );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�N���X�̍X�V����
	bg.Update();
	player.Update();
	npc.Update();

	float player_screen_x = player.m_pos.x - camera_x;
	if (player_screen_x > X_RIGHT)
	{
		float x = player_screen_x - X_RIGHT;
		camera_x += x;
	}
	else if (player_screen_x < X_LEFT)
	{
		float x = player_screen_x - X_LEFT;
		camera_x += x;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	//	�N���X�̕`�揈��
	bg.Render(camera_x);
	npc.Render(camera_x);
	player.Render(camera_x);

	DrawLine( X_RIGHT, 0, X_RIGHT, SCREEN_H, GetColor( 0, 255, 255 ) );

	DrawString( 16, 16, "���E�L�[�F�v���C���[�̈ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�v���C���[�͐��F�̐����E�ɍs���Ȃ��i����ɑ������������j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�X�y�[�X�F�W�����v", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	
	bg.Exit();
	player.Exit();
	npc.Exit();

	DeleteGraph( bg_image );
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
