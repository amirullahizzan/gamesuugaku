#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#include "Player.h"
#include "Npc.h"
#include "BG.h"

//	�f�[�^�p�̕ϐ�
int bg_image;		//	�w�i�p
int player_image;	//	�v���C���[
int npc_image;		//	�m�o�b
//	�u�������������Łi���Ԃ���������j.exe�v�p�̉摜�p�ϐ�
int mini_player_image;	//	�~�j�v���C���[�摜

//	�N���X�̐錾
BG		bg;			//	�w�i
Player	player;		//	�v���C���[
Npc		npc;		//	�m�o�b

//	�`�悷�邽�߂ɍ��W���ǂꂾ�����炷��
float game_offset_x;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�f�[�^�̓ǂݍ���
	bg_image = LoadGraph( "data/bg.bmp" );			//	�R�O�O�O���S�T�O
	player_image = LoadGraph( "data/player.bmp" );	//	�E����
	npc_image = LoadGraph( "data/npc.bmp" );		//	������
	//	�~�j�v���C���[�摜�̓ǂݍ���
	//	�u�������������Łi���Ԃ���������j.exe�v�p�ɓǂݍ��݂������Ă��܂�
	mini_player_image = LoadGraph( "data/mini_player.bmp" );

	//	�ǂݍ��񂾃f�[�^��n���ď�����
	bg.Init( bg_image );
	player.Init( player_image );
	npc.Init( npc_image );

	//	����� 0.0f ����J�n
	game_offset_x = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�N���X�̍X�V����
	bg.Update();		//	���ɉ������Ȃ�
	player.Update();	//	���E�L�[�ŉ��ړ��E�X�y�[�X�L�[�ŃW�����v
	npc.Update();		//	���ɉ������Ȃ�

	//	����̎d�l�Ƃ��܂��ẮA��̒l�i X_RIGHT�F��ʍ��W�j����
	//	�v���C���[�̉�ʍ��W���ǂ̂��炢�傫�����̔��f�ɂȂ�܂�
	//	�Ƃ����킯�ŁA�v���C���[�̉�ʍ��W�����߂܂�
	float player_screen_x = player.m_pos.x - game_offset_x;
	//	���̉�ʍ��W������W�𒴂��Ă�����
	if( player_screen_x > X_RIGHT ){
		//	�ǂꂾ�������Ă��邩
		float x = player_screen_x - X_RIGHT;
		//	���̕���������𑝂₵�܂�
		game_offset_x += x;
	}
	else if (player_screen_x < X_LEFT)
	{
		player.m_pos.x = game_offset_x + X_LEFT;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�N���X�̕`�揈���i�S�� Base �N���X�� Render �֐����Ă�ł��܂��j
	//	�ǂꂾ�����ꂽ����n���ĕ`��֐����Ăт܂�
	bg.Render( game_offset_x );
	npc.Render( game_offset_x );
	player.Render( game_offset_x );
	Float2 linepos;
	linepos.x = 20;
	linepos.y = 120;
	float player_initpos = 200.0f;
	const float initpos_miniplayer = 320 / player_initpos;
	DrawLine  (linepos.x												, linepos.y, 300 + 20, 120, GetColor(0,0,0), 1);
	DrawGraphF(linepos.x + game_offset_x * (300.0f / 3000.0f) + 20,	105	,mini_player_image,1);

	//	�ڈ��̐��i�v���C���[�͂����荶�ɂ͈ړ����Ȃ��j
	DrawLine( X_LEFT, 0, X_LEFT, SCREEN_H, GetColor( 255, 0, 0 ) );

	//	�ڈ��̐��i�v���C���[������ȏ�E�ɍs��������肪�����j
	DrawLine( X_RIGHT, 0, X_RIGHT, SCREEN_H, GetColor( 0, 255, 255 ) );

	DrawString( 16, 16, "���E�L�[�F�v���C���[�̈ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�v���C���[�͐��F�̐����E�ɍs���Ȃ��i����ɑ������������j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "���@���ړ��͐Ԃ����Ŏ~�߂�", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�X�y�[�X�F�W�����v", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "�m�o�b�͈��Ԋu�ŃW�����v���J��Ԃ�", GetColor( 255, 255, 0 ) );
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

	DeleteGraph( mini_player_image );
}
