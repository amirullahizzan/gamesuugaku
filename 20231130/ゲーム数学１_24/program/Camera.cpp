#include "Main.h"
#include "Game.h"
#include "Camera.h"



//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Camera::Init()
{
	
	//m_pos.x =   0.0f;
	//m_pos.y =  20.0f;
	//m_pos.z = -30.0f;
	m_pos.set(0,20,30);

	/*m_look.x = 0.0f;
	m_look.y = 0.0f;
	m_look.z = 0.0f;*/
	m_look.clear();

	m_camera_type = TYPE_STAGE;
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Camera::Update(Float3 player_pos)
{
	if (PushHitKey(KEY_INPUT_F1)) { m_camera_type = TYPE_STAGE; }
	if (PushHitKey(KEY_INPUT_F2)) { m_camera_type = TYPE_PLAYER; }

	switch (m_camera_type)
	{
	case TYPE_STAGE:
		m_pos.set(0.0f, 20.0f, -30.0f);
		m_look.clear();
		break;

	case TYPE_PLAYER:
		m_look.set(player_pos);
		
		m_pos.x = m_look.x + 0.0f;
		m_pos.y = m_look.y + 7.0f;
		m_pos.z = m_look.z - 15.0f;
		break;
	}
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY( VGet( m_pos.x, m_pos.y, m_pos.z ), VGet( m_look.x, m_look.y, m_look.z ) );
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
