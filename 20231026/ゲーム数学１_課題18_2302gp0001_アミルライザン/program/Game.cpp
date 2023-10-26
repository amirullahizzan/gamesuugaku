#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"

//	�v���C���[�E�m�o�b�̔��a�i�����蔻��Ŏg���܂��j
#define CHARA_RADIUS	25.0f

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_SPEED	5.0f

#define BAR_X 600
//	�v���C���[�ϐ�
int		player_image;	//	�摜
Float2	player_pos;		//	���W
int		player_hp;		//	�g�o
int		player_hp_bar;		//	�g�o
int		player_hp_display;		//	�g�o
int immune_delay = 0;
const int MAX_PLAYER_HP = 5;
int bar_color_i = 0;

//	�m�o�b�̈ړ��X�s�[�h
#define NPC_SPEED		3.0f
//	�m�o�b�ϐ�
int		npc_image;		//	�摜
Float2	npc_pos;		//	���W

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );

	player_pos.x = 100.0f;
	player_pos.y = 200.0f;
	//	�g�o�T�ŊJ�n
	player_hp = 5;

	npc_pos.x = 500.0f;
	npc_pos.y = 300.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�Ńv���C���[�ړ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_pos.x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_pos.x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_pos.y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_pos.y -= PLAYER_SPEED;

	//	�m�o�b�̈ړ�����
	npc_pos.x -= NPC_SPEED;
	if( npc_pos.x < 0.0f ){
		npc_pos.x = SCREEN_W;
		npc_pos.y = GetRand( SCREEN_H );
	}
	const int HP_BAR_WIDTH = 500;

		immune_delay--; 
		if (immune_delay <= 0) { immune_delay = 0; }
	//	�v���C���[�Ƃm�o�b������������
	if( CheckCircleHit( player_pos, CHARA_RADIUS, npc_pos, CHARA_RADIUS ) ){
		//	�g�o���P���炷
		if (immune_delay<=0)
		{
			player_hp -= 1;
			if (player_hp <= 0)
			{
			player_hp = 0;
			}
			immune_delay = 50;
			player_hp_bar+= HP_BAR_WIDTH / MAX_PLAYER_HP;
			
		}
	}
	if (player_hp_display > player_hp_bar)
	{
		player_hp_display--;
		
	}
	else if (player_hp_display < player_hp_bar)
	{
		player_hp_display++;
	}

	if (player_hp_display >= HP_BAR_WIDTH)
	{
		player_hp_display = HP_BAR_WIDTH;
	}

	if (player_hp_display < HP_BAR_WIDTH/2)
	{

		bar_color_i = 0;
	}
	else
	{
		bar_color_i = 1;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̕`��
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( 180.0f ), npc_image, TRUE );

	int bar_color[2];
	bar_color [0] = GetColor(0,255,0);
	bar_color [1] = GetColor(255,0,0);

	//	�v���C���[�̕`��
	if (immune_delay % 3 == 0 || immune_delay == 0)
	{
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( 0.0f ), player_image, TRUE );
	}

	//	�g�o�o�[�̔����g�̎l�p�i�w���W 100 �` 600 �ŕ��� 500 �ɂ��Ă��܂��j
	//int barpoint = player_hp % BAR_X;
	DrawFillBox(100,100, BAR_X- player_hp_display,120,bar_color[bar_color_i]);
	DrawLineBox( 100, 100, BAR_X, 120, GetColor( 255, 255, 255 ) );

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�v���C���[�Ƃm�o�b������������g�o���P����i�ł��G�͏����Ȃ��j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "���@�v���C���[�͓����������莞�ԓ_�Łi���̊Ԃ͖��G�j", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�g�o�ɍ��킹���o�[���l�p���g���ĕ`��", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "���@�o�[�̒����������ȉ��̎��͐F��ς���", GetColor( 255, 255, 0 ) );

	//	�g�o�𕶎���ŕ`��
	DrawFormatString( 16, 103, GetColor( 0, 255, 255 ), "�g�o�F%d", player_hp );

	clsDx();
	printfDx("%d",player_hp_display);
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
