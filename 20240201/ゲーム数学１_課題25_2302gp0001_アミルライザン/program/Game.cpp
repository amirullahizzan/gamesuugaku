#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;
//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
//	�m�o�b�N���X�͕����錾
#define NPC_MAX	8
Npc		npc[NPC_MAX];

//	�~�j�}�b�v�摜�p�̕ϐ�
int mini_map_image;		//	�~�j�}�b�v�̔w�i�摜
int mini_player_image;	//	�~�j�v���C���[
int mini_npc_image;		//	�~�j�m�o�b

int mapMode = 0;

//	�~�j�}�b�v�̊�̍��W
Float2 center_map;		//	�R�c��Ԃ̌��_�𒆐S�ɂ����~�j�}�b�v�̒��S���W
Float2 player_map;		//	�v���C���[�����S�̃~�j�}�b�v

const int MAP_SIZE = 200;
const int MAP_SIZE_HALF = MAP_SIZE * 0.5;

Float2 mapIndicatorPos = { 16,64 };

bool isAnimationMode = false;
int animationMode = 0;
int mapInfoMode = 0;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------


void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	���f���f�[�^�ԍ���n���ăN���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}
	//	�~�j�}�b�v�摜�̓ǂݍ���
	mini_map_image = LoadGraph( "data/mini_map.bmp" );			//	�~�j�}�b�v�̔w�i�摜
	mini_player_image = LoadGraph( "data/mini_player.bmp" );	//	�~�j�v���C���[
	mini_npc_image = LoadGraph( "data/mini_npc.bmp" );			//	�~�j�m�o�b
	//	���ꂼ��̃~�j�}�b�v�̒��S���W
	center_map.set( 120.0f, 330.0f );	//	�Z���^�[�}�b�v
	player_map.set( 0.0f - MAP_SIZE_HALF, 330.0f );	//	�v���C���[�}�b�v
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------


void GameUpdate()
{
	ground.Update();
	//	���E�L�[�Ō�����ς��ď�L�[�ňړ�
	player.Update();

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		animationMode = 1;
		if (mapMode == 0)
		{ 
			mapIndicatorPos = { mapIndicatorPos.x,80 }; 
		}
		else
		{
			mapIndicatorPos = { mapIndicatorPos.x,64 };
		}
	}

	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	�v���C���[���W�I�b�n���ăJ�����̐ݒ�
	camera.Update( player.m_pos );
}

void MapAreaFocus()
{
	//	�Z���^�[�}�b�v�̕`��
//---------------------------------------------
//	�������̐ݒ�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//	�Z���^�[�}�b�v�̔w�i�摜�̕`��
	DrawRotaGraphF(center_map.x, center_map.y, 1.0f, TO_RADIAN(0.0f), mini_map_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	�~�j�m�o�b�̕`��
	for (int i = 0; i < NPC_MAX; i++) {
		float nx = center_map.x + npc[i].m_pos.x * 10.0f;
		float ny = center_map.y - npc[i].m_pos.z * 10.0f;
		DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, TRUE);
	}

	//	�v���C���[�̂R�c���W���Q�c�ɂ��ă}�b�v�ɕ`��
	//	�w���W�F�Z���^�[�}�b�v�̒��S����A�R�c�̂w���W���P�O�{�����Ƃ���
	float px = center_map.x + player.m_pos.x * 10.0f;
	//	�x���W�F�R�c�̉����Q�c�̉��ɂȂ��Ă��܂��̂ŋt������
	float py = center_map.y - player.m_pos.z * 10.0f;
	//	���̍��W���~�j�}�b�v���̎�����
	if (px > center_map.x - 100.0f && px < center_map.x + 100.0f) {
		if (py > center_map.y - 100.0f && py < center_map.y + 100.0f) {
			//	���̍��W�Ń~�j�v���C���[�摜�̕`��i�摜�̌����̓��f���̂x���̉�]���g���āj
			DrawRotaGraphF(px, py, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, TRUE);
		}
	}
}

void MapPlayerFocus()
{
	//---------------------------------------------
//	�v���C���[�}�b�v�̕`��
//---------------------------------------------
//	�v���C���[�}�b�v�̔w�i�摜�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRotaGraphF(player_map.x, player_map.y, 1.0f, TO_RADIAN(0.0f), mini_map_image, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//	�~�j�m�o�b�̕`��
	for (int i = 0; i < NPC_MAX; i++) {
		//	�v���C���[���猩�����ɂm�o�b���ǂ̕����ɂ��邩���g���č��W�����߂܂�
		float nx = player_map.x + (npc[i].m_pos.x - player.m_pos.x) * 10.0f;
		float ny = player_map.y - (npc[i].m_pos.z - player.m_pos.z) * 10.0f;
		//	���̍��W���~�j�}�b�v�͈̔͊O��������`�揈�������Ȃ��Ń��[�v������
		if (nx < player_map.x - 100.0f)	continue;
		if (nx > player_map.x + 100.0f)	continue;
		if (ny < player_map.y - 100.0f)	continue;
		if (ny > player_map.y + 100.0f)	continue;
		//	�`�揈��
		DrawRotaGraphF(nx, ny, 1.0f, TO_RADIAN(npc[i].m_rot.y), mini_npc_image, TRUE);
	}

	//	�~�j�v���C���[�̕`��i��Ƀ~�j�}�b�v�̒��S�A�����͂R�c�v���C���[�̌����ɍ��킹��j
	DrawRotaGraphF(player_map.x, player_map.y, 1.0f, TO_RADIAN(player.m_rot.y), mini_player_image, TRUE);
}


//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�R�c�`��̂��߂̃J�����̐ݒ�
	camera.Render();
	//	���ꂼ��̃��f���̕`��
	ground.Render();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	//	�~�j�}�b�v�̕`��
	//---------------------------------------------
	Float2 animPos;
	Float2 animPos2;

	
	clsDx();
	//printfDx(" centermap %f", center_map.x);
	//printfDx(" playermap %f", player_map.x);
	printfDx(" mapindi %f", mapIndicatorPos.y);
	const float animSpeed = 5.2f;
	static int fontsize_half = GetFontSize() * 0.5f;
	DrawCircle(mapIndicatorPos.x, mapIndicatorPos.y + fontsize_half, 6, COLOR_YELLOW, 1);

	switch (mapMode)
	{
	case 0:
		MapAreaFocus();
		//DrawCircle(16, 64 + fontsize_half, 6, COLOR_YELLOW, 1);

		if (center_map.x + MAP_SIZE_HALF > 0 && animationMode == 1)
		{
			animPos.x -= animSpeed;
		}
		else if (center_map.x <= 120.0f && animationMode == 2)
		{
			animPos.x += animSpeed;
		}
		else
		{
			animationMode = 0;
		}

		if (center_map.x + MAP_SIZE_HALF <= 0)
		{
			mapMode = 1;
			animationMode = 2;
		}
		center_map.x += animPos.x;

		break;

	case 1:
		MapPlayerFocus();

		if (player_map.x + MAP_SIZE_HALF > 0 && animationMode == 1)
		{
			animPos2.x -= animSpeed;
		}
		else if (player_map.x <= 120.0f && animationMode == 2)
		{
			animPos2.x += animSpeed;
		}
		else
		{
			animationMode = 0;
		}

		if (player_map.x + MAP_SIZE_HALF <= 0)
		{
			mapMode = 0;
			animationMode = 2;
		}
		player_map.x += animPos2.x;
		break;
	}

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�ǂ��炩�̃~�j�}�b�v����ʍ����ɕ\��", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�X�y�[�X�L�[�F�~�j�}�b�v�̐؂�ւ�", GetColor( 255, 255, 0 ) );

	

	DrawString( 16, 64, "�@�R�c�̌��_�����S�̃~�j�}�b�v", GetColor( 255, 255, 0 ) );
	DrawString( 16, 80, "�@�v���C���[�����S�̃~�j�}�b�v", GetColor( 255, 255, 0 ) );


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

	DeleteGraph( mini_map_image );
	DeleteGraph( mini_player_image );
	DeleteGraph( mini_npc_image );
}
