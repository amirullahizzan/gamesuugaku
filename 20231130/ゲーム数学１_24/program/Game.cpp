#include "Main.h"
#include "Game.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

Ground ground;
Player player;
Camera camera;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	ground.Init();
	player.Init();
	camera.Init();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	player.Update();
	camera.Update(player.m_pos);
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("angle : %f", player.m_rot.y);

	camera.Render();
	ground.Render();
	player.Render();

	DrawString( 16, 16, "�N���X�Ŏ���", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�\���L�[�F�v���C���[�ړ��i������ς��āj", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�X�y�[�X�F�W�����v", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�e�P�L�[�F�X�e�[�W�S�̂�����J����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 80, "�e�Q�L�[�F�v���C���[������J����", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	ground.Exit();
	player.Exit();
	camera.Exit();
}
