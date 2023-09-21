#include "Main.h"
#include "Game.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOV_SPEED	5.0f
//	�v���C���[�̉�]�X�s�[�h�i�x�j
#define PLAYER_ROT_SPEED	3.0f

//	�I�v�V�������v���C���[����ǂꂾ������邩
//	�߂�����
#define LENGTH_NEAR		50.0f
//	��������
#define LENGTH_FAR		100.0f
//	�I�v�V�����̐�
#define OPTION_MAX		6

//	�v���C���[�p�̕ϐ�
int player_image;	//	�摜
float player_x;		//	�w���W
float player_y;		//	�x���W
float player_rot;	//	����

//	�I�v�V�����p�̕ϐ�
int option_image;	//	�摜�i�����摜���g���܂킻���Ǝv���܂��̂ŃI�v�V�����摜�͂P�j
float option_x[OPTION_MAX];		//	�w���W
float option_y[OPTION_MAX];		//	�x���W
float option_rot[OPTION_MAX];	//	����

//	�v���C���[����I�v�V�����܂ł̊�̋���
float base_length;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	option_image = LoadGraph( "data/option.bmp" );
	//	�v���C���[�̏����ݒ�
	player_x = 100.0f;
	player_y = 250.0f;
	player_rot = 0.0f;
	//	�X�V�����ł����ɍ��W��������ݒ肳���̂ł����Ƃ肠����
	for( int i = 0; i < OPTION_MAX; i++ ){
		option_x[i] = 100.0f + 50.0f * i;
		option_y[i] = 300.0f;
		option_rot[i] = 0.0f;
	}
	//	�J�n���͋߂���������n�߂�
	base_length = LENGTH_NEAR;
}

float rotator = 0;

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
		//	���̒����������W�ړ�
		player_x += mov_x;
		player_y += mov_y;
	}

	//	���V�t�g�L�[�ŋ����̕ύX
	if( CheckHitKey( KEY_INPUT_LSHIFT ) ){
		//	�����Ă���Ƃ��͉�������
		if (base_length <= LENGTH_FAR)
		{
		base_length+=5;
		}
	}else{
		if (base_length >= LENGTH_NEAR)
		{
			//	�����Ă��Ȃ��Ƃ��͋߂�����
			base_length-=5;
		}
	}
	//	�v���C���[�̍��W�ƌ����̍X�V���I���܂����̂Łi���������܂����̂Łj���̏�Ԃ��炻�ꂼ��̃I�v�V�����̍��W����������肵�܂�
	for( int i = 0; i < OPTION_MAX; i++ ){

		//	�v���C���[�̌����i�ɂX�O�x�������������j�� base_length �����炷���߂̂w�����Ƃx�����̒��������߂܂�
		
		rotator+=0.5;
		if (rotator>=360)
		{
			rotator = 0;
		}
		float mov_x = base_length * GetLength_RotSotte( TO_RADIAN( player_rot + 360/OPTION_MAX * i +rotator) );	//	GetLength_RotSotte �� cos �֐��̂��Ƃł�
		float mov_y = base_length * GetLength_RotMukai( TO_RADIAN( player_rot + 360/ OPTION_MAX * i + rotator) );	//	GetLength_RotMukai �� sin �֐��̂��Ƃł�

		//	�I�v�V�������W�̓v���C���[���W�����ŋ��߂��������i�񂾂Ƃ���
		option_x[i] = player_x + mov_x;
		option_y[i] = player_y + mov_y;

		//	�v���C���[�̌����ɍ��킹��
		option_rot[i] = player_rot;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�v���C���[���W�ƌ�����n���ăv���C���[�摜�̕`��
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	//	�I�v�V�����̕`��
	for( int i = 0; i < OPTION_MAX; i++ ){
		DrawRotaGraphF( option_x[i], option_y[i], 1.0f, TO_RADIAN( option_rot[i] ), option_image, TRUE );
	}

	DrawString( 20,  20, "�����L�[�F�v���C���[��]", GetColor( 255, 255, 255 ) );
	DrawString( 20,  40, "���@�L�[�F�v���C���[�̌����Ă�������Ɉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 20,  60, "�I�v�V�����𑝂₵�ăv���C���[�̎������]�����Ă݂�", GetColor( 255, 255, 0 ) );
	DrawString( 20,  80, "���V�t�g�L�[�F�I�v�V�����̋�����������", GetColor( 255, 255, 255 ) );
	DrawString( 20, 100, "���@�����̐؂�ւ����X���[�Y��", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( option_image );
}
