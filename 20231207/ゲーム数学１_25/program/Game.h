#pragma once

#define SCREEN_W	800
#define SCREEN_H	450

void GameInit();	//	����������
void GameUpdate();	//	�X�V����
void GameRender();	//	�`�揈��
void GameExit();	//	�I������

//	�X�e�[�W�͈̔�
#define STAGE_X_MIN	-20.0f	//	�w���W��������
#define STAGE_X_MAX	 20.0f	//	�w���W�����܂�
#define STAGE_Z_MIN	-10.0f	//	�y���W��������
#define STAGE_Z_MAX	 30.0f	//	�y���W�����܂�
