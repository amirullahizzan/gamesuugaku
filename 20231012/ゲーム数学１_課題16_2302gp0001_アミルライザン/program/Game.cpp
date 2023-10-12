#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Float2.h"		//	hit.h �̒��� Float2.h �C���N���[�h���Ă��邯�ǂ����ł��C���N���[�h���Ƃ��܂�

//	�v���C���[�Ƃm�o�b�̔��a
#define CHARA_RADIUS	25.0f

//	�v���C���[�p�̕ϐ�
int player_image;		//	�摜
Float2 player_pos;		//	���W�i�w���W�Ƃx���W�̂Q�� float ������\���́j
float player_rot;		//	�����i�x�j
//	�v���C���[�̈ړ���
Float2 player_mov;

//	�m�o�b�p�̕ϐ�
int npc_image;
Float2 npc_pos;
float npc_rot;

//	�}�E�X���W������p�̕ϐ��i�X�V�����ƕ`�揈���Ń}�E�X���W�̒l���g���̂Łj
Float2 mouse;

//	�}�E�X�h���b�O�����ǂ���
bool mouse_drag;

Float2 point_pos;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�������W������̐ݒ�
	//	�Ƃ肠������ʒ����ɕ\�����Ƃ��܂�
	player_pos.x = SCREEN_W / 2;
	player_pos.y = SCREEN_H / 2;
	player_rot = 0.0f;

	npc_pos.x = GetRand( SCREEN_W );
	npc_pos.y = GetRand( SCREEN_H );
	npc_rot = 0.0f;
}

float drag_x;
float drag_y;

void GameUpdate()
{
	//	�}�E�X���W�̎擾
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	�}�E�X���������u��
	if( PushMouseInput() ){
		//	�P�F�}�E�X�̂Ƃ���Ƀv���C���[��u��
		point_pos.x = mouse.x;
		point_pos.y = mouse.y;
	}

	//	�}�E�X�������Ă���Ƃ�
	if( CheckMouseInput() ){
		//	�}�E�X�������Ă���̂�
		mouse_drag = true;
		player_pos.x = mouse.x;
		player_pos.y = mouse.y;

		//	�Q�F�v���C���[�̌������}�E�X���W�̕���
		//	�v���C���[����}�E�X���W���ǂꂾ���i�񂾂Ƃ���ɂ��邩
		drag_x = point_pos.x - player_pos.x;
		drag_y = point_pos.y - player_pos.y;

		//	��ŋ��߂��v���C���[����}�E�X�܂ł̒l���ړ��ʂƂ��Ď����Ă����܂�
		//	���̂܂܂��Ƒ傫������̂œK���ɏ��������܂��i 0.05 �{���܂��j
		player_mov.x = drag_x * 0.05f;
		player_mov.y = drag_y * 0.05f;

		//	���̒l���g���Ċp�x�����߂܂�
//		float radian = GetRadian_LengthYX( y, x );
		//	���������ŒZ������ player_mov ���g���Ă������p�x�����炦�܂�
		float radian = GetRadian_LengthYX( player_mov.y, player_mov.x );
		//	�v���C���[�̊p�x�ϐ��́u�x�v�Ȃ̂ŁA���W�A���p��x�ɕϊ����ēn���܂�
		player_rot = TO_DEGREE( radian ); 

	}else{
		//	�����Ă��Ȃ��̂�
		mouse_drag = false;

		//	�}�E�X�������Ă���Ƃ��Ɍ��߂��ړ��ʂ��g���ăv���C���[�̍��W�̍X�V
		player_pos.x += player_mov.x;
		player_pos.y += player_mov.y;
	}

	//	�m�o�b�̉�]
	npc_rot += 1.0f;

	//	�v���C���[�Ƃm�o�b�̓����蔻��i�~���m�̓����蔻��j
	if( CheckCircleHit( player_pos, CHARA_RADIUS, npc_pos, CHARA_RADIUS ) ){
		//	������������W�������_����
		npc_pos.x = GetRand( SCREEN_W );
		npc_pos.y = GetRand( SCREEN_H );
	}

	if (player_pos.x > SCREEN_W-CHARA_RADIUS || player_pos.x < 0 + CHARA_RADIUS )
	{
		player_mov.x *= -1;

	

		player_rot = TO_DEGREE(atan2f (player_mov.y, player_mov.x) );
	}
	if (player_pos.y > SCREEN_H - CHARA_RADIUS || player_pos.y < 0 + CHARA_RADIUS)
	{
		player_mov.y *= -1;
		player_rot = TO_DEGREE(atan2f(player_mov.y, player_mov.x));

	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̕`��
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );
	//	�v���C���[�̕`��
	DrawRotaGraphF( player_pos.x, player_pos.y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	//	�}�E�X�h���b�O���̎�
	if( mouse_drag ){
		//	�v���C���[���W�ƃ}�E�X���W����Ō���
		DrawLineAA( point_pos.x, point_pos.y, mouse.x, mouse.y, GetColor( 255, 255, 0 ) );
		//	�}�E�X���W�̂Ƃ���ɉ~�̕`��
		DrawCircleAA( point_pos.x, point_pos.y, 5.0f, 100, GetColor( 255, 255, 0 ) );
	}

	DrawString( 16, 16, "�}�E�X�N���b�N�F�N���b�N���W�ݒ�", GetColor( 255, 255, 0 ) );
	DrawString( 16, 32, "�}�E�X�h���b�O�F�}�E�X�̏��Ƀv���C���[��u���i�v���C���[�̓N���b�N���W�̕��������j", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "���@�v���C���[�ƃN���b�N���W�����񂾐���`��", GetColor( 255, 255, 0 ) );
	DrawString( 16, 64, "�}�E�X�{�^���𗣂�����v���C���[�͌����Ă�������Ɉړ�����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "���@���������قǈړ�������", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "�v���C���[�Ƃm�o�b�œ����蔻��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
