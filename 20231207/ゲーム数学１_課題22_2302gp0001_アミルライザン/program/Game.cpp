#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�̔ԍ�������ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

#define NPC_MAX		5
Npc		npc[NPC_MAX];
class Area : public Base
{
public:
	void Init() 
	{
		m_pos.set(AREA_X_MAX - AREA_X_MIN, 0.0f, AREA_Z_MAX - AREA_Z_MIN);
		m_rot.set(0.0f, 0.0f, 0.0f);
		m_size.set(AREA_X_MIN, 0.5f, AREA_Z_MIN);
	}
};
Area area;
//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�e���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	���ꂼ��̃N���X�̏������֐����Ă�
	//	�J�����̏�����
	camera.Init();
	//	���f���ԍ���n���Ă��ꂼ��̃N���X�̏�����
	ground.Init( ground_model );
	player.Init( player_model );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}
	area.Init();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�N���X�̍X�V����
	ground.Update();
	//	�\���L�[�ō��W�ړ�
	player.Update();
	//	���ɉ������Ă��܂���
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	�v���C���[�Ƃm�o�b�œ����蔻��
	for( int i = 0; i < NPC_MAX; i++ ){
		//	�{�b�N�X���m�œ����蔻��
		if( CheckBoxHit3D( player.m_pos, player.m_size, npc[i].m_pos, npc[i].m_size ) ){
			//	����������m�o�b�̍��W�������_���ɐݒ�
			npc[i].SetRandom();
		}
	}

	//	�v���C���[���W��n���ăJ�����̍X�V�������Ăт܂�


	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void ForceCam()
{
	//	�J�����̌�����W�̍����͒n�ʂ̍�����
	camera.m_look.y = 0.0f;

	//	�J�������W�͌�����W�����藣�ꂽ�Ƃ���
	camera.m_look.x = (AREA_X_MIN + AREA_X_MAX) / 2;
	camera.m_look.z = (AREA_Z_MIN + AREA_Z_MAX) / 2;
	camera.m_pos.x = camera.m_look.x + 0.0f;
	camera.m_pos.y = camera.m_look.y + 9.0f;
	camera.m_pos.z = camera.m_look.z - 10.0f;
}

int m_lastcammode = 0;
void GameRender()
{
	clsDx();
	printfDx("player x: %f\n\n",player.m_pos.x);
	printfDx("player x: %f\n\n",player.m_pos.y);
	printfDx("player x: %f\n\n",player.m_pos.z);

	printfDx("area x: %f\n",area.m_pos.x);
	printfDx("area x: %f\n", area.m_pos.y);
	printfDx("area x: %f\n", area.m_pos.z);

	printfDx("size x: %f\n",area.m_size.x);
	printfDx("size x: %f\n", area.m_size.y);
	printfDx("size x: %f\n", area.m_size.z);
	VECTOR vector = {area.m_pos.x,area.m_pos.y,area.m_pos.z};
	VECTOR vector2 = {area.m_size.x,area.m_size.y,area.m_size.z};

	printfDx("size x: %f\n", vector.x);
	printfDx("size x: %f\n", vector.y);
	printfDx("size x: %f\n", vector.z);
	DxLib::DrawCube3D(vector,vector2,GetColor(0,0,0), GetColor(0, 0, 0),1);
	if (CheckBoxHit3D(player.m_pos, player.m_size, area.m_pos, area.m_size)	)
	{
		ForceCam();
		//exit(0);
	}
	
	camera.Render();
	//	�n�ʃ��f���̕`��ƃX�e�[�W�͈͂̐��̕`��
	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�O�̘g�ɓ��������璵�˕Ԃ�悤�ȓ���", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "���@�v���C���[�Ƃm�o�b�œ����蔻��i����������m�o�b�̍��W�������_���ݒ�j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�X�y�[�X�F�W�����v", GetColor( 255, 255, 255 ) );

	DrawString( 16, 80, "�e�P�L�[�F�S�̃J����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 96, "�e�Q�L�[�F�v���C���[�J����", GetColor( 255, 255, 255 ) );

	DrawString( 16, 112, "�v���C���[���l�p�̃G���A�ɓ���ƃG���A�J������", GetColor( 0, 255, 255 ) );

	DrawString( 16, 128, "�m�o�b���w�����ړ��i�O�g�ɓ���������ړ��ʂ̔��]�j", GetColor( 0, 255, 255 ) );
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
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}
}
