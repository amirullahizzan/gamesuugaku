#include "Main.h"
#include "Game.h"

//	�v���C���[�摜�p�̕ϐ�
#define GROUND_Y 300

int player_image;
//	�v���C���[���W
float player_x;
float player_y;
//	�v���C���[�̈ړ��X�s�[�h�p�̕ϐ�
float player_speed;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ��݂Ə������W�̐ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	//	float �^�̕ϐ��ɐ��l��ݒ肷��̂ŁAfloat �ƕ�����悤�Ɍ��� f ��t���Ă܂�
	player_x = 100.0f;
	player_y = 100.0f;
	//	�����X�s�[�h
	player_speed = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player_x-=2;
	}
	else if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		player_x+=2;
	}


	//	�X�s�[�h�ϐ��̒l����ɑ��₵�Ă����܂�

	player_y += player_speed;

	//	�v���C���[�̍��W�ړ��i�c�����Ɉړ����������̂łx���W��ύX���܂��j

	if (player_y < GROUND_Y-0.3f)
	{
		player_speed += 0.3f;

	}
	else
	{
		player_speed = 0;
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			player_speed = -10;
		}
	}
	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[�̕`��i�`�悷�邽�߂̍��W�� float �^�Ȃ̂Łj
	DrawGraphF( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "��ʉ��ɗ����ړ��i�X�s�[�h�𑝂₵�Ȃ��牺�ړ��j", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "��ʉ��ɏ����Ȃ��悤�ɓK���ȂƂ���łx���W���~�߂�", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "�X�y�[�X�F�W�����v�i��ʏ�����Ɉړ��ʂ�ݒ�j", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
}
