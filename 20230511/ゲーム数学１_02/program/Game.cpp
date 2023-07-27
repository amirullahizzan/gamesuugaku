#include "Main.h"
#include "Game.h"
#include "../Control.h"
#include "../Init.h"


int player_image;
int npc_image;

int playerx = 0;
int playery = 0;
double playerrotation = 0;
int enemyx = 0;
//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	LoadBMP();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------

void GameUpdate()
{
	PlayerControl();
	enemyx--;
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		enemyx = 0;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	
	DrawRotaGraph(200 + playerx, 100,1,playerrotation, player_image, TRUE,0);
	//DrawGraph( 200+playerx, 100, player_image, TRUE );
	DrawGraph( 500+enemyx, 300, npc_image, TRUE );

	DrawString( 20, 20, "�����L�[�F�v���C���[�ړ��i��ʊO�ɂ͂����Ȃ��j", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "�X�y�[�X�F�m�o�b�̍��W�̐ݒ�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
