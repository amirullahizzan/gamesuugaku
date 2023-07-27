#include "Main.h"
#include "Game.h"

//	�P�F�摜��ǂݍ��񂾎��̔ԍ�������p�̕ϐ���p��
//	�v���C���[�摜
int player_image;
//	�v���C���[�̂w���W�̒l������p�̕ϐ�
int player_x;
int player_y;

//	�m�o�b�摜
int npc_image;
//	�m�o�b�̂w���W
int npc_x;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�Q�F�摜�t�@�C����ǂݍ���Ŕԍ����擾
	//	�v���C���[�摜
	player_image = LoadGraph( "data/player.bmp" );
	//	�v���C���[�̏����w���W
	player_x = 200;
	player_y = 100;

	//	�m�o�b�摜
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�m�o�b�̏����w���W
	npc_x = 500;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�v���C���[�͍��E�L�[�ō��E�ړ�
	//	�E�L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	��ʉE�Ɉړ����������̂łw���W�p�̕ϐ��̒l�𑝂₵�܂�
		player_x += 5;
		//	�v���C���[����ʉE�Ŏ~�߂���
		//	�v���C���[�摜�� 100 x 100 �̑傫���Ȃ̂�
		//	�v���C���[�I�ȉ�ʂ̈�ԉE�� 700 = ��ʃT�C�Y 800 - �摜�T�C�Y 100
		if( player_x > 700 ){
			player_x = 700;
		}
	}
	//	���L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//	���Ɉړ�
		player_x -= 5;
		//	�v���C���[�͉�ʍ��܂ōs������~�܂�
		if( player_x < 0 ){
			player_x = 0;
		}
	}

	if (CheckHitKey(KEY_INPUT_UP)) {
		//	���Ɉړ�
		player_y -= 5;
		//	�v���C���[�͉�ʍ��܂ōs������~�܂�
		if (player_y < 0) {
			player_y = 0;
		}
	}

	if (CheckHitKey(KEY_INPUT_DOWN)) {
		//	���Ɉړ�
		player_y += 5;
		//	�v���C���[�͉�ʍ��܂ōs������~�܂�
		if (player_y > 350) {
			player_y = 350;
		}
	}

	//	�m�o�b�͍��Ɉړ��i�w���W�̒l�����炵�Ă����j
	npc_x -= 2;

	//	�X�y�[�X�L�[���������u�Ԃ����m�o�b�̍��W��ݒ肷��
	if( PushHitKey( KEY_INPUT_SPACE ) ){
		npc_x = 500;
	}
	if (npc_x <= -100)
	{
		npc_x = 800;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�R�F���̔ԍ����g���ĕ`��i�����F����Łj
	//	�v���C���[�̕`��i�w���W�Fplayer_x�@�x���W�F100 �j
	DrawGraph( player_x, player_y, player_image, TRUE );

	//	�m�o�b�̕`��i�w���W�Fnpc_x�@�x���W�F300 �j
	DrawGraph( npc_x, 300, npc_image, TRUE );

	DrawString( 20, 20, "�\���L�[�F�v���C���[�̏㉺���E�̈ړ��i��ʊO�ɂ͂����Ȃ��j", GetColor( 255, 255, 0 ) );
	DrawString( 20, 40, "�X�y�[�X�F�m�o�b�̍��W�̐ݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "���@��ʂ̍��܂ōs������E����o�Ă���", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	//	�S�F�ǂݍ��񂾂��̂̏I������
	//	�v���C���[
	DeleteGraph( player_image );
	//	�m�o�b
	DeleteGraph( npc_image );
}
