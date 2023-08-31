#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	3.0f
//	�m�o�b�̈ړ��X�s�[�h
#define NPC_SPEED		2.0f
//	���ꂼ��̔��a
#define RADIUS			25.0f

//	�v���C���[�p�̕ϐ�
int player_image;		//	�摜
float player_x;			//	�w���W
float player_y;			//	�x���W
float player_rot;		//	�����i�p�x�̓x�j

//	�m�o�b��
int npc_image;
float npc_x;
float npc_y;
float npc_rot;		//	��]����̂Ŋp�x�p�̕ϐ��i�x�j

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ��݂Ə������W�̐ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;
	//	�E��������J�n�i�E�����F�O�x�j
	player_rot = 0.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 500.0f;
	npc_y = 300.0f;
	npc_rot = 0.0f;
}

int game_frame = 0;
int npc_facing = 0;
int npc_facing_previous = 0;
int facing_timer_rand = 1;

void NPCAI()
{
	enum 
	{
		DOWN = 0, LEFT = 1, UP= 2, RIGHT = 3
	};

	if (game_frame % (facing_timer_rand) == 0)
	{
		facing_timer_rand = 10 * (GetRand(10)+1);
		npc_facing = GetRand(3);
		while(npc_facing == npc_facing_previous)
		{
			npc_facing = GetRand(3);
			break;
		}
		npc_facing_previous = npc_facing;
	}
		switch (npc_facing)
		{
		case DOWN:
			npc_rot = 90.0f;
			npc_y+=NPC_SPEED;
			break;
		case LEFT:
			npc_rot = 180.0f;
			npc_x-= NPC_SPEED;
			break;
		case UP:
			npc_rot = 270.0f;
			npc_y-= NPC_SPEED;
			break;
		case RIGHT:
			npc_rot = 0.0f;
			npc_x += NPC_SPEED;
			break;
		}
}

void GameUpdate()
{
	game_frame++;

	NPCAI();
	//	�\���L�[�ō��W�ړ��i���łɌ������ς���j
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		//	�E�����ɂ������̂łO�x
		player_rot = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		//	�������͂P�W�O�x
		player_rot = 180.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		//	�������ɂ������̂łX�O�x
		player_rot = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		//	������F�Q�V�O�x
//		player_rot = 270.0f;
		//	������F�[�X�O�x
		player_rot = -90.0f;
	}

	if (npc_x > SCREEN_W)
	{
		npc_x = 0;
	}
	if (npc_x < 0 )
	{
		npc_x = SCREEN_W;
	}
	if (npc_y > SCREEN_H)
	{
		npc_y = 0;
	}
	if (npc_y < 0)
	{
		npc_y = SCREEN_H;
	}
		
	//	����͂m�o�b�̏�ɉ�]�̏����͓���Ă��܂���


	//	�v���C���[�Ƃm�o�b�œ����蔻��i�~���m�Łj
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		//	����������m�o�b�̍��W����ʓ��̂ǂ��������_���ɐݒ�
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = (float)GetRand( SCREEN_H );
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���W�ƌ�����ݒ�ł���`��֐����g���܂�

	
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	//	�v���C���[�̌��� player_rot�i�x�j �����W�A���p�ɕϊ� TO_RADIAN ���ĕ`��֐��ɓn���܂�
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�m�o�b�̓v���C���[�Ɠ�����ƍ��W�Đݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "�m�o�b�͓K���Ȏ��Ԃ������烉���_���Ɍ�����ς���", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "���@�㉺���E�Ɍ�����ς��ď㉺���E�Ɉړ�", GetColor( 255, 255, 0 ) );
	DrawFormatString(20, 280, GetColor(255, 255, 120), "Facing : %d", npc_facing);
	DrawFormatString(20, 300, GetColor(255, 255, 120), "Facing Timer : %d", facing_timer_rand);

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	//	�ǂݍ��񂾉摜�̏I������
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
