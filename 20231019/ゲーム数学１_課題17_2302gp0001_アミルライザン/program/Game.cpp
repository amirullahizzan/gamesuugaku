#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

//	�m�o�b�̍ő吔
#define NPC_MAX			5
//	�m�o�b�̈ړ��X�s�[�h
#define NPC_MOV_SPEED	1.0f
//	�m�o�b�̉�]�X�s�[�h�i�x�j�F�������������ɂ��̃X�s�[�h�ŉ�]���Ă����܂�
#define NPC_ROT_SPEED	0.5f

//	�����蔻��p�̔��a
#define NPC_RADIUS	25.0f

//	�m�o�b�̕ϐ�
int		npc_image;	//	�摜
Float2	npc_pos[NPC_MAX];	//	���W
float	npc_rot[NPC_MAX];	//	�����i�x�j�F���̌����̒l��ڕW�̌����ɂ��Ă���
int pos_sequencer = -1;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	npc_image = LoadGraph( "data/npc.bmp" );

	for (int i = 0;i<NPC_MAX;i++)
	{
	npc_pos[i].x= GetRand(500.0f);
	npc_pos[i].y= GetRand(350.0f);
	npc_rot[i] = 0.0f;
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�}�E�X���W�i�m�o�b���������������W�j
	Float2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	//	�P�F���̍��W�i npc_pos �j����ڕW���W�i mouse �j�ւ̌��������߂�
	//	�P�|�P�F���̍��W����ڕW���W�܂łǂ̂��炢��
	for (int i = 0; i < NPC_MAX; i++)
	{

	float x = mouse.x - npc_pos[i].x;
	float y = mouse.y - npc_pos[i].y;
	//	�P�|�Q�F���̒l���g���Č��������߂�i���̌������ŏI�I�Ɍ������������j
	float goal_rot = TO_DEGREE( GetRadian_LengthYX( y, x ) );	//	GetRadian_LengthYX�Fatan2f

	//	�Q�F���̌����i npc_rot �j����ڕW�̌����i goal_rot �j�܂łǂ̂��炢�̍��i next_rot �j�����邩
	float next_rot = goal_rot - npc_rot[i];
	//	�Q�|�P�F��ŋ��߂��p�x�̍��� -180.0f �` 180.0f �ɂ�����
	//	�P�W�O�x���z���Ă��镪�͂P�����i�R�U�O�x�j����
	while( next_rot >= 180.0f )	next_rot -= 360.0f;
	while( next_rot < -180.0f )	next_rot += 360.0f;

	//	�R�F�p�x�̍������ĉ�]�����܂��i���̍����v���X�Ȃ瑫���Ă����}�C�i�X�Ȃ�����Ă����j
	if( next_rot >= NPC_ROT_SPEED ){			//	�v���X�����ɉ�]�X�s�[�h�ȏ�傫��������
		npc_rot[i] += NPC_ROT_SPEED;				//	�v���X��]������
	}else if( next_rot <= -NPC_ROT_SPEED ){		//	��]�X�s�[�h�������Ȃ�
		npc_rot[i] -= NPC_ROT_SPEED;				//	�}�C�i�X��]������
	}else{										//	����Ȃ����i�قڐ��ʂ̎��j
		npc_rot[i] = goal_rot;						//	�ڕW�̌����ɂ���
	}

	//	�m�o�b�̌����Ă�������ɍ��W�ړ�
	npc_pos[i].x += NPC_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( npc_rot[i]) );	//	GetLength_RotSotte�Fcosf
	npc_pos[i].y += NPC_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( npc_rot[i]) );	//	GetLength_RotMukai�Fsinf

	//	�}�E�X�Ƃm�o�b�i�~�Ƃ��āj�œ����蔻��i�_�Ɖ~�̓����蔻��j

	if( CheckPointCircleHit( mouse, npc_pos[i], NPC_RADIUS ) ){
		//	������������W������������_���ɐݒ�
		pos_sequencer++;
		switch (pos_sequencer)
		{
		case 0:
			npc_pos[i].x = 0;	//	0 �` 800
			npc_pos[i].y = 0;	//	0 �` 450
			npc_rot[i] = GetRand(90) + 90 -90;

			break;
		case 1:
			npc_pos[i].x = SCREEN_W;	//	0 �` 800
			npc_pos[i].y = 0;	//	0 �` 450
			npc_rot[i] = GetRand(90) + 90;

			break;
		case 2:
			npc_pos[i].x = SCREEN_W;	//	0 �` 800
			npc_pos[i].y = SCREEN_H;	//	0 �` 450
			npc_rot[i] = GetRand(90) + 180;

			break;
		case 3:
			npc_pos[i].x = 0;	//	0 �` 800
			npc_pos[i].y = SCREEN_H;	//	0 �` 450
			npc_rot[i] = GetRand(90) + 270;

			pos_sequencer = -1;
			break;
		}
		
	}

	}

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̕`��
	for (int i = 0; i < NPC_MAX; i++)
	{
	DrawRotaGraphF( npc_pos[i].x, npc_pos[i].y, 1.0f, TO_RADIAN( npc_rot[i]), npc_image, TRUE );
	}

	DrawString( 16, 16, "�m�o�b�̓}�E�X���W�Ɍ������Ĉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�}�E�X���W�Ɠ�����������W������̍Đݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�m�o�b�́u���̉�]�X�s�[�h�v�Ń}�E�X���W�̕��֌�����ς��Ȃ���ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�m�o�b�����ɂ���i�������W������������_���Ɂj", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "�m�o�b�Đݒ���W�͉�ʂ́u����E�E��E�E���E�����v�̂ǂꂩ", GetColor( 255, 255, 0 ) );
	DrawString( 16, 96, "���@���������̓o��ꏊ�����ʓ��Ɍ������ă����_���Ȍ�����", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( npc_image );
}
