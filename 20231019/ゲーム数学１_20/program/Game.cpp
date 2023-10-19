#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Hit.h"

#define NPC_MOV_SPEED	1.0f
#define NPC_ROT_SPEED	1.0f

#define NPC_RADIUS	25.0f

int		npc_image;
Float2	npc_pos;
float	npc_rot;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	npc_image = LoadGraph( "data/npc.bmp" );

	npc_pos.x = 500.0f;
	npc_pos.y = 350.0f;
	npc_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	Float2 mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();

	{
		float dx = mouse.x - npc_pos.x;
		float dy = mouse.y- npc_pos.y;
		//float toMouse_rot = 180/3.14*atan2f(dy,dx);
		float toMouse_rot = TO_DEGREE(GetRadian_LengthYX(dy,dx));

	
		//npc_rot = toMouse_rot;

		float rot_offset = toMouse_rot - npc_rot;

		//prevent over revolting
		if (rot_offset >= 180)
		{
			rot_offset -= 360;
		}
		if (rot_offset < -180)
		{
			rot_offset += 360;
		}

		/*if (rot_offset > 0)
		{
			npc_rot+= NPC_ROT_SPEED; 
		}
		if (rot_offset < 0)
		{
			npc_rot-=NPC_ROT_SPEED;
		}*/
		//�Ԃ�Ă�

		if (rot_offset >= NPC_ROT_SPEED)
		{
			npc_rot+= NPC_ROT_SPEED;
		}
		else if (rot_offset <= -NPC_ROT_SPEED)
		{
			npc_rot-=NPC_ROT_SPEED;
		}
		/*else
		{
			npc_rot = toMouse_rot;
		}*/
		
		

	

	}

	npc_pos.x += NPC_MOV_SPEED * GetLength_RotSotte( TO_RADIAN( npc_rot ) );
	npc_pos.y += NPC_MOV_SPEED * GetLength_RotMukai( TO_RADIAN( npc_rot ) );

	if( CheckPointCircleHit( mouse, npc_pos, NPC_RADIUS ) ){
		npc_pos.x = GetRand( SCREEN_W );
		npc_pos.y = GetRand( SCREEN_H );
		npc_rot = GetRand( 360 );
	}
	
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawRotaGraphF( npc_pos.x, npc_pos.y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	Float2 line_pos;
	//line_pos.x = 300*cosf(TO_RADIAN(npc_rot));
	//line_pos.y = 300*sinf(TO_RADIAN(npc_rot));
	
	line_pos.x = 300 * cosf(3.14 / 180 * npc_rot);
	line_pos.y = 300 * sinf(3.14 / 180 * npc_rot);
	DrawLine(npc_pos.x,npc_pos.y, npc_pos.x + line_pos.x, npc_pos.y + line_pos.y, GetColor(255,255,0),1);

	DrawString( 16, 16, "�m�o�b�̓}�E�X���W�Ɍ������Ĉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�}�E�X���W�Ɠ�����������W������̍Đݒ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�m�o�b�́u���̉�]�X�s�[�h�v�Ń}�E�X���W�̕��֌�����ς��Ȃ���ړ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	DeleteGraph( npc_image );
}
