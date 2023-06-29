#include "Main.h"
#include "Game.h"

//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
int player_x;		//	�w���W
int player_y;		//	�x���W
//	�m�o�b
int npc_image;
int npc_x[11];
int npc_y[11];
//	�A�C�e��
int item_image;
int item_x;
int item_y;

//---------------------------------------------------------------------------------
//	�_�Ǝl�p�̓����蔻�������֐�
//		point_x	�F�n���ꂽ�_�̂w���W
//		point_y	�F�@�@�@�@�@�@�x���W
//		box_x	�F�n���ꂽ�l�p�̂w���W
//		box_y	�F�@�@�@�@�@�@�@�x���W
//		box_w	�F�@�@�@�@�@�@�@����
//		box_h	�F�@�@�@�@�@�@�@����
//	�O�F�������Ă��Ȃ��@�P�F�������Ă���
//---------------------------------------------------------------------------------
int CheckPointBoxHit( int point_x, int point_y, int box_x, int box_y, int box_w, int box_h )
{
	//	�_�̂w���W���l�p�̍��ƉE�̊�
	if( point_x >= box_x && point_x <= box_x + box_w ){
		//	�_�̂x���W���l�p�̏�Ɖ��̊�
		if( point_y >= box_y && point_y <= box_y + box_h ){
			//	�֐��̌��ʂƂ��ē������Ă���̂łP��Ԃ��܂�
			return 1;
		}
	}
	//	�������Ă��Ȃ��̂łO��Ԃ��܂�
	return 0;
}

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ��݂Ə������W�̐ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 300;
	player_y = 100;

	for (int i = 0;i<11;i++)
	{
	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x[i] = GetRand(SCREEN_W)+200;
	npc_y[i] = GetRand(SCREEN_H);
	}

	item_image = LoadGraph( "data/item.bmp" );
	item_x = 500;
	item_y = 300;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	��ʍ��Ɉړ�
	player_x -= 1;
	//	��ʂ̍��܂ōs������
	if( player_x < -50 ){
		//	�E����o�Ă���
		player_x = 800;
		//	�x���W�̓����_����
		player_y = GetRand( 400 );
	}

	for(int i = 0; i < 11; i++)
	{
	npc_x[i] -= 2;
	if( npc_x[i] < -50 ){
		npc_x[i] = 800;
		npc_y[i] = GetRand( 400 );
	}
	}

	item_x -= 3;
	if( item_x < -50 ){
		item_x = 800;
		item_y = GetRand( 400 );
	}

	//	�}�E�X���N���b�N�����Ƃ�
	if( PushMouseInput() ){
		//	�}�E�X���W���擾
		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();

		//	�}�E�X�ƃv���C���[�̓����蔻��
		int check = CheckPointBoxHit( mouse_x, mouse_y, player_x, player_y, 50, 50 );
		//	�������Ă�����v���C���[����ʉE�ɂ�����
		if( check == 1 ){
			player_x = 800;
			player_y = GetRand( 400 );
		}

	
		for (int i = 0; i < 11; i++)
		{
		//	�}�E�X�Ƃm�o�b�œ����蔻��
		if( CheckPointBoxHit( mouse_x, mouse_y, npc_x[i], npc_y[i], 50, 50) == 1) {
			//	�������Ă�����m�o�b���E��
			npc_x[i] = 800;
			npc_y[i] = GetRand( SCREEN_H ) - 50;
		}
		}

		//	�}�E�X�ƃA�C�e���̓����蔻��
		if( CheckPointBoxHit( mouse_x, mouse_y, item_x, item_y, 50, 50 ) ){
			//	�������Ă�����A�C�e������ʉE��
			item_x = GetRand(SCREEN_W) + SCREEN_W;
			item_y = GetRand( 400 );
			for (int i = 0; i < 11; i++)
			{
				npc_x[i] = SCREEN_W + GetRand(SCREEN_W);
				npc_y[i] = GetRand(SCREEN_H)-50;
			}

		}
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���ꂼ��̍��W�ɂ��ꂼ��̉摜��`��
	DrawGraph( item_x, item_y, item_image, TRUE );

	for (int i = 0; i < 11; i++)
	{
	DrawGraph( npc_x[i], npc_y[i], npc_image, TRUE );
	}

	DrawGraph( player_x, player_y, player_image, TRUE );

	DrawString( 20, 20, "�v���C���[�E�m�o�b�E�A�C�e�����}�E�X�ŃN���b�N", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�m�o�b�𕡐���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "�A�C�e�����N���b�N������m�o�b�S���������������", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( item_image );
}
