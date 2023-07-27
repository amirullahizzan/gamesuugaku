#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	�ړ��X�s�[�h
#define PLAYER_SPEED	 3.0f	//	�v���C���[
#define NPC_SPEED		 3.0f	//	�m�o�b
#define MISSILE_SPEED	10.0f	//	�~�T�C��

//	�傫��
#define NPC_SIZE		50.0f	//	�m�o�b
#define MISSILE_SIZE	20.0f	//	�~�T�C��

//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
float player_x;		//	�w���W
float player_y;		//	�x���W

//	�m�o�b
int npc_image;
float npc_x;
float npc_y;

//	�~�T�C��
int missile_image;
//	�~�T�C���̐�
#define MISSILE_MAX	100
//	���W
float missile_x[MISSILE_MAX];
float missile_y[MISSILE_MAX];
//	���~�T�C�����ǂ�ȏ�ԂȂ̂��i�O�F���ł��Ȃ��@�P�F���ł���j
int missile_mode[MISSILE_MAX];

int timerms;
						
int icon_image;

int icon_x[MISSILE_MAX];

int killcount;


void GameInit()
{
	//	�摜�̓ǂݍ��݂Ə������W�̐ݒ�
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 700.0f;
	npc_y = 300.0f;
	//	�~�T�C���摜�̓ǂݍ���
	missile_image = LoadGraph( "data/missile.bmp" );
	icon_image = LoadGraph("data/icon.bmp");

	killcount = 0;


	//	�S�~�T�C���̏�����
	for( int i = 0; i < MISSILE_MAX; i++ )
	{
		icon_x[i] = -60;
		//	�~�T�C�����W�̏����ݒ�i�Ƃ肠�����j
		missile_x[i] = 0.0f;
		missile_y[i] = 0.0f;
		//	�~�T�C���͔��ł��Ȃ���Ԃ���J�n
		missile_mode[i] = 0;
	}
	timerms = 0;
	

}


void AddKillCount()
{
		icon_x[killcount] = 20*killcount;
		killcount++;
}

bool CanBoostTime()
{
	return killcount >= 3;
}

int attackdelay = 10;
const int constboostduration = 200;
int boostduration = 200;

bool isBoostTime = false;


bool isBoostKeepTrack = false;

void BoostReset()
{
	if (isBoostTime)
	{
		boostduration--;
		if (boostduration <= 0 && isBoostTime)
		{
			//reset
			attackdelay = 10;
			boostduration = constboostduration;
			isBoostTime = false;
		}
	}
}

void ActivateBoost()
{
	killcount = 0;
	isBoostTime = true;

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		icon_x[i] = -100;
	}
	attackdelay = 2;
	isBoostKeepTrack = true;
	
}



void GameUpdate()
{
	//	�\���L�[�Ńv���C���[�̍��W�ړ�
	timerms++;

	if(timerms >= attackdelay)
	{
		for (int i = 0; i < MISSILE_MAX; i++) 
		{
			//	�~�T�C�������ł��Ȃ���Ԃ̎�
			if (missile_mode[i] == 0) {
				//	�~�T�C�����ԏ�ԂɕύX
				missile_mode[i] = 1;
				//	���[�v�𔲂���
				break;
			}

		}
		timerms = 0;

	}

	if( CheckHitKey( KEY_INPUT_RIGHT ) )	player_x += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		player_x -= PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_DOWN ) )		player_y += PLAYER_SPEED;
	if( CheckHitKey( KEY_INPUT_UP ) )		player_y -= PLAYER_SPEED;
	
	if (CheckHitKey(KEY_INPUT_SPACE) && CanBoostTime())
	{
		ActivateBoost();
	}

	BoostReset();
	//	�X�y�[�X�L�[��
		//	�S�Ẵ~�T�C�������Ă����Ĕ��ł��Ȃ����̂��������炻����΂���Ԃɂ��āu���[�v���I��点��v
		

	//	�S�~�T�C���̈ړ�����
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	�~�T�C�������łȂ��Ƃ�
		if( missile_mode[i] == 0 ){
		
			missile_x[i] = player_x + 15.0f;	//	15.0f = 25.0f - 10.0f
			missile_y[i] = player_y + 15.0f;
		}
		//	�~�T�C�������ł���Ƃ�
		if( missile_mode[i] == 1 ){
			//	��ʉE�Ɉړ�������
			missile_x[i] += MISSILE_SPEED;
			//	��ʂ̉E�܂ōs������
			if( missile_x[i] > SCREEN_W ){
				//	�~�T�C�����΂Ȃ���Ԃ�
				missile_mode[i] = 0;
			}
		}
	}

	//	�m�o�b�͉�ʍ��Ɉړ�
	npc_x -= NPC_SPEED;
	//	��ʂ̍��܂ōs������
	if( npc_x < -NPC_SIZE ){
		//	�E����o�Ă���
		npc_x = SCREEN_W;
	}

	//	�S�~�T�C���Ƃm�o�b�œ����蔻��
	for( int i = 0; i < MISSILE_MAX; i++ ){
		//	�~�T�C�������ł�����Ƃ�
		if( missile_mode[i] == 1 ){
			//	�ړ���̃~�T�C���Ƃm�o�b�œ����蔻��i�l�p���m�̓����蔻��j
			if( CheckBoxHit( missile_x[i], missile_y[i], MISSILE_SIZE, MISSILE_SIZE, npc_x, npc_y, NPC_SIZE, NPC_SIZE ) ){
				//	�������Ă�����
				//	�~�T�C�����΂Ȃ���Ԃɂ��܂�
				missile_mode[i] = 0;
				AddKillCount();
				//	�m�o�b�̍��W���Đݒ�
				npc_x = SCREEN_W;
				npc_y = (float)GetRand( SCREEN_H - NPC_SIZE );
			}
		}
	}
}

void GameRender()
{
	//	�m�o�b�̕`��
	DrawGraphF( npc_x, npc_y, npc_image, TRUE );

	//	�~�T�C���̕`��
	for( int i = 0;i < MISSILE_MAX; i++ ){
		//	���ł���~�T�C���̂�
		if( missile_mode[i] == 1 ){
			DrawGraphF( missile_x[i], missile_y[i], missile_image, TRUE );
		}
	}

	//	�v���C���[�̕`��
	DrawGraphF( player_x, player_y, player_image, TRUE );

	for (int i = 0; i < MISSILE_MAX; i++)
	{
		DrawGraphF(20 + icon_x[i], 100, icon_image, TRUE);
	}

	DrawString( 20, 20, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�����ň��Ԋu�Ń~�T�C������", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "NPC��|�������������A�C�R������ׂĂ݂�", GetColor( 150, 200, 225 ) );

	if (CanBoostTime())
	{
		DrawString(20, 300, "Press SPACE to Boost!", GetColor(225, 220, 120));

	}
}

void GameExit()
{
	//	�ǂݍ��񂾉摜�̏I������
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
	DeleteGraph( missile_image );
}
