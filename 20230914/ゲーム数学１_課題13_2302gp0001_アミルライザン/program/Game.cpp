#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOV_SPEED	5.0f
//	�v���C���[�̉�]�X�s�[�h�i�x�j
#define PLAYER_ROT_SPEED	3.0f
//	�~�T�C���̈ړ��X�s�[�h
#define MISSILE_SPEED		10.0f

//	�v���C���[�p�̕ϐ�
int player_image;		//	�摜
float player_x;			//	�w���W
float player_y;			//	�x���W
float player_rot;		//	�����i�x�j

//	�~�T�C���̐�
#define MISSILE_MAX		300

//	�~�T�C���p�̕ϐ�
int missile_image;		//	�摜�i�������̂��g���܂킻���Ǝv���̂Ŕz��ɂ͂��Ă��Ȃ��ł��j
float missile_x[MISSILE_MAX];		//	�w���W
float missile_y[MISSILE_MAX];		//	�x���W
float missile_rot[MISSILE_MAX];		//	�����i�x�j
//	�~�T�C���̃��[�h
enum {
	MODE_WAIT,	//	�O�F���ł��Ȃ�
	MODE_MOVE,	//	�P�F���ł���
};
int missile_mode[MISSILE_MAX];		//	�~�T�C���������[�h���i�O�F���ł��Ȃ��@�P�F���ł���j

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ��݂Ə����ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 200.0f;
	player_rot = 0.0f;

	//	�~�T�C���摜�̓ǂݍ���
	missile_image = LoadGraph( "data/missile.bmp" );
	//	�~�T�C���̐���������
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	�Ƃ肠�����i 100 100 �j�ɂ��Ă��܂����A�ŏI�I�ɂ͌����Ȃ���Ԃ���n�܂�܂�
		missile_x[i] = 100.0f;
		missile_y[i] = 100.0f;
		//	�������O�x�ɂ��Ă��܂����A��������v���C���[�̌����ɂȂ�
		missile_rot[i] = 0.0f;
		//	�ŏ��͔��ł��Ȃ���Ԃ���J�n
		missile_mode[i] = MODE_WAIT;
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
int rotatingmissile = 0;
void GameUpdate()
{
	//	���E�L�[�Ńv���C���[�̌����̕ύX
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_rot += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_rot -= PLAYER_ROT_SPEED;

	//	��L�[�Ō����Ă�������Ɉړ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	�w�����ɂ��ꂾ���i�ށi���� PLAYER_MOV_SPEED �� player_rot ��]�������Ƃ��̊p�x�ɉ����Ă���ق��̒����j
		float mov_x = PLAYER_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( player_rot ) );
		//	�x�����ɂ��ꂾ���i�ށi���� PLAYER_MOV_SPEED �� player_rot ��]�������Ƃ��̊p�x�̌������ɂ���ق��̒����j
		float mov_y = PLAYER_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( player_rot ) );
		//	���̈ړ������������������W�ɑ���
		player_x += mov_x;
		player_y += mov_y;
	}

	//	�X�y�[�X�L�[����������~�T�C������
	if( PushHitKey( KEY_INPUT_SPACE ) ){
		//	�~�T�C�����P������������
		for( int i = 0; i < MISSILE_MAX; i++ ){
			//	�~�T�C�������ł��Ȃ��Ƃ�����
			if( missile_mode[i] == MODE_WAIT ){
				//	�~�T�C�����ԏ�ԂɕύX
				missile_mode[i] = MODE_MOVE;
				//	�~�T�C���̍��W���v���C���[�ɍ��킹�܂�
				missile_x[i] = player_x;
				missile_y[i] = player_y;
				//	�~�T�C���̌������v���C���[�ɍ��킹�܂�
				missile_rot[i] = player_rot;

				//	�X�y�[�X�L�[�������ă~�T�C�������̂͂P�������ɂ������̂Ń��[�v���I��点�܂�
				break;
			}
		}
	}

	if( PushHitKey( KEY_INPUT_1 ) ){
		for (int j = 0; j < 3; j++)
		{
		for( int i = 0; i < MISSILE_MAX; i++ ){
			if( missile_mode[i] == MODE_WAIT )
			{
				missile_mode[i] = MODE_MOVE;
				missile_x[i] = player_x;
				missile_y[i] = player_y;
				missile_rot[i] = player_rot + j * 20.0f - 20.0f;
				break;
			}
		}
		}
	}

	if( PushHitKey( KEY_INPUT_2 ) )
	{
		for (int j = 0; j < 36; j++)
		{
			for (int i = 0; i < MISSILE_MAX; i++)
			{
				if (missile_mode[i] == MODE_WAIT)
				{
					missile_mode[i] = MODE_MOVE;
					missile_x[i] = player_x;
					missile_y[i] = player_y;
					missile_rot[i] = player_rot + (10 * j);
					break;
				}
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_3)) 
	{
		if (rotatingmissile >= 36)
		{
			rotatingmissile = 0;
		}
		rotatingmissile++;
			for (int i = 0; i < MISSILE_MAX; i++)
			{
				if (missile_mode[i] == MODE_WAIT)
				{
					missile_mode[i] = MODE_MOVE;
					missile_x[i] = player_x;
					missile_y[i] = player_y;
					missile_rot[i] = player_rot + (10 * rotatingmissile);
					break;
				}
			}
	}


	//	�~�T�C���̈ړ�����
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	�~�T�C�������ł���Ƃ��݈̂ړ�����
		if( missile_mode[i] == MODE_MOVE ){
			//	�~�T�C�����w�����ɂ��ꂾ���i��
			float mov_x = MISSILE_SPEED * GetLength_RotSotte( TO_RADIAN( missile_rot[i] ) );
			//	�x������
			float mov_y = MISSILE_SPEED * GetLength_RotMukai( TO_RADIAN( missile_rot[i] ) );
			//	���̕��������W�ړ�
			missile_x[i] += mov_x;
			missile_y[i] += mov_y;

			//	��ʂ̊O�ɏo�����΂Ȃ���Ԃɂ��܂�
			if( missile_x[i] <     0.0f )	missile_mode[i] = MODE_WAIT;
			if( missile_x[i] > SCREEN_W )	missile_mode[i] = MODE_WAIT;
			if( missile_y[i] <     0.0f )	missile_mode[i] = MODE_WAIT;
			if( missile_y[i] > SCREEN_H )	missile_mode[i] = MODE_WAIT;
		}
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	�~�T�C�������ł���Ƃ�����
		if( missile_mode[i] == MODE_MOVE ){
			//	�~�T�C����`�悵�܂�
			DrawRotaGraphF( missile_x[i], missile_y[i], 1.0f, TO_RADIAN( missile_rot[i] ), missile_image, TRUE );
		}
	}

	//	�v���C���[�̍��W�ƌ�����n���ăv���C���[�摜�̕`��
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20,  20, "�����L�[�F�v���C���[��]", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�L�[�F�v���C���[�̌����Ă�������Ɉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "�X�y�[�X�F�~�T�C������", GetColor( 255, 255, 255 ) );
	DrawString( 20,  80, "�P�L�[�@�F�R�����~�T�C��", GetColor( 255, 255, 0 ) );
	DrawString( 20, 100, "�Q�L�[�@�F�R�U�O�x�~�T�C��", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( missile_image );
}
