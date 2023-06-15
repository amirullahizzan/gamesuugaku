#include "Main.h"
#include "Game.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	5
//	�m�o�b�̃X�s�[�h
#define NPC_SPEED		3

//	�v���C���[�摜
int player_image;
//	�v���C���[���W
int player_x;
int player_y;

//	�m�o�b�摜
int npc_image;
//	�m�o�b���W
int npc_x;
int npc_y;

//	�u������܂����v��\�������邽�߂̃J�E���^�[
int draw_frame;

//	��摜�p�̕ϐ�
int sky_image;
//	�n�ʉ摜�p�̕ϐ�
int ground_image;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	��摜�E�n�ʉ摜�̓ǂݍ���
	sky_image = LoadGraph( "data/sky.bmp" );
	ground_image = LoadGraph( "data/ground.bmp" );

	//	�摜�̓ǂݍ��݂Ə������W�̐ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100;
	player_y = 200;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 300;
	npc_y = 300;

	draw_frame = 0;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
int skymover = 0;
int groundmover = 0;


bool isPlayerStunned = false;
void GameUpdate()
{
	//	�\���L�[����������v���C���[���W�̍X�V
	if (!isPlayerStunned)
	{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	}

	if (player_x < 0)
	{
		player_x = 0;
	}
	if (player_x > SCREEN_W-50)
	{
		player_x = SCREEN_W-50;
	}
	if (player_y < 0)
	{
		player_y = 0;
	}
	if (player_y > SCREEN_H-50)
	{
		player_y = SCREEN_H-50;
	}

	//	�m�o�b�̍��W�ړ�
	//	��ʍ��Ɉړ�
	npc_x -= NPC_SPEED;
	//	��ʂ̍��ɍs������
	if( npc_x < -50 ){
		//	�E�ɖ߂�
		npc_x = 800;
		//	�x���W�̓����_����
		npc_y = GetRand( 400 );
	}

	//	�v���C���[�Ƃm�o�b�œ����蔻��i�l�p���m�̓����蔻��j
	if( player_x <= npc_x + 50 && player_x + 50 >= npc_x ){
		if( player_y <= npc_y + 50 && player_y + 50 >= npc_y ){
			//	�������Ă�����m�o�b�̍��W���Đݒ�
			npc_x = 800;
			//	�x���W�������_����
			npc_y = GetRand( 400 );

			//	�\�����Ԃ̃Z�b�g�i�P�b�F�U�O�t���[���Ȃ̂Łj
			draw_frame = 60;

			isPlayerStunned = true;
			
		}
	}

	

	//	������\���J�E���^�[�̒l�����炵�Ă���
	draw_frame--;
	if( draw_frame < 0 ){
		draw_frame = 0;
		isPlayerStunned = false;
	}

	
	skymover+= 2;

	if (skymover > 800)
	{
		skymover = 0;
	}

	groundmover += 4;

	if (groundmover > 800)
	{
		groundmover = 0;
	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�Ƃ肠������ʍ���ɕ\���������Ă��܂��i�ۑ�̎���������̂ł���̓R�����g�ɂ��܂��j
	DrawGraph(0-skymover, 0, sky_image, TRUE);
	DrawGraph( SCREEN_W-skymover, 0, sky_image, TRUE );

	DrawGraph( 0- groundmover, 400, ground_image, TRUE );
	DrawGraph(400 - groundmover, 400, ground_image, TRUE);
	DrawGraph(400 + 400 - groundmover, 400, ground_image, TRUE);
	DrawGraph(800+400- groundmover, 400, ground_image, TRUE);


	//	�m�o�b�̕`��
	DrawGraph( npc_x, npc_y, npc_image, TRUE );
	//	�v���C���[�̕`��
	DrawGraph( player_x, player_y, player_image, TRUE );

	//	����������J�E���^�[�̒��ɒl�������Ă���P�b�Ԃ���
	if( draw_frame > 0 ){
		DrawString( 20, 150, "������܂���", GetColor( 255, 255, 0 ) );
	}

	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ��i��ʊO�ɍs���Ȃ��i�n�ʂ�艺�ɂ������Ȃ��j", GetColor( 255, 255, 0 ) );
	DrawString( 20, 40, "�m�o�b���n�ʂ�艺�ɂ͂����Ȃ�", GetColor( 255, 255, 0 ) );
	DrawString( 20, 60, "�v���C���[�Ƃm�o�b��������Ƃm�o�b�̍��W�Đݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 80, "�u������܂����v�\�����v���C���[�͈ړ����ł��Ȃ�", GetColor( 255, 255, 0 ) );

	DrawString( 20, 100, "�w�i�\���ƃX�N���[���@(��F�������@�n�ʁF��������)", GetColor( 40, 200, 240 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( sky_image );
	DeleteGraph( ground_image );
}
