#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	�L�����̔��a
#define CHARA_RADIUS	0.5f

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	���E�L�[�ŉ�]�E��L�[�ňړ�
	player.Update();
	npc.Update(player.m_pos);

	//	���ꂼ��̍��W�̍X�V���I���܂����̂ŋ����m�œ����蔻������܂�
	if( CheckBallHit( player.m_pos, CHARA_RADIUS, npc.m_pos, CHARA_RADIUS ) ){
		//	�m�o�b�̍��W�������_����
		npc.m_pos.x = GetRandomF( -10.0f, 10.0f );
		npc.m_pos.z = GetRandomF( -10.0f, 10.0f );
		//	������ 0.0f �` 360.0f �̃����_��
		npc.m_rot.y = GetRandomF( 360.0f );
	}

	camera.Update();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�����ĕ`��J�n
	camera.Render();
	//	���f���̕`��
	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�m�o�b�̓v���C���[�̕��Ɍ�����ς��Ȃ���ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�v���C���[�Ƃm�o�b�œ����蔻��@���@����������m�o�b�̍��W�������_���ɐݒ�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );

	camera.Exit();
	ground.Exit();
	player.Exit();
	npc.Exit();
}
