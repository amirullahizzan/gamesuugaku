#include "Main.h"
#include "Game.h"
#include "Hit.h"

//	ƒvƒŒƒCƒ„[‚ÌˆÚ“®ƒXƒs[ƒh
#define PLAYER_SPEED	3.0f
//	‚m‚o‚b‚ÌˆÚ“®ƒXƒs[ƒh
#define NPC_SPEED		2.0f
//	‚»‚ê‚¼‚ê‚Ì”¼Œa
#define RADIUS			25.0f

//	ƒvƒŒƒCƒ„[—p‚Ì•Ï”
int player_image;		//	‰æ‘œ
float player_x;			//	‚wÀ•W
float player_y;			//	‚xÀ•W
float player_rot;		//	Œü‚«iŠp“x‚Ì“xj

//	‚m‚o‚b‚à
int npc_image;
float npc_x;
float npc_y;
float npc_rot;		//	‰ñ“]‚·‚é‚Ì‚ÅŠp“x—p‚Ì•Ï”i“xj

//---------------------------------------------------------------------------------
//	‰Šú‰»ˆ—
//---------------------------------------------------------------------------------
void GameInit()
{
	//	‰æ‘œ‚Ì“Ç‚Ýž‚Ý‚Æ‰ŠúÀ•W‚ÌÝ’è
	player_image = LoadGraph( "data/player.bmp" );
	player_x = 100.0f;
	player_y = 100.0f;
	//	‰EŒü‚«‚©‚çŠJŽni‰EŒü‚«F‚O“xj
	player_rot = 0.0f;

	npc_image = LoadGraph( "data/npc.bmp" );
	npc_x = 500.0f;
	npc_y = 300.0f;
	npc_rot = 0.0f;
}

int game_frame = 0;
int npc_facing = 0;
int npc_facing_previous = 0;
int facing_timer_rand = 1;

void NPCAI()
{
	enum 
	{
		DOWN = 0, LEFT = 1, UP= 2, RIGHT = 3
	};

	if (game_frame % (facing_timer_rand) == 0)
	{
		facing_timer_rand = 10 * (GetRand(10)+1);
		npc_facing = GetRand(3);
		while(npc_facing == npc_facing_previous)
		{
			npc_facing = GetRand(3);
			break;
		}
		npc_facing_previous = npc_facing;
	}
		switch (npc_facing)
		{
		case DOWN:
			npc_rot = 90.0f;
			npc_y+=NPC_SPEED;
			break;
		case LEFT:
			npc_rot = 180.0f;
			npc_x-= NPC_SPEED;
			break;
		case UP:
			npc_rot = 270.0f;
			npc_y-= NPC_SPEED;
			break;
		case RIGHT:
			npc_rot = 0.0f;
			npc_x += NPC_SPEED;
			break;
		}
}

void GameUpdate()
{
	game_frame++;

	NPCAI();
	//	\ŽšƒL[‚ÅÀ•WˆÚ“®i‚Â‚¢‚Å‚ÉŒü‚«‚à•Ï‚¦‚éj
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		player_x += PLAYER_SPEED;
		//	‰EŒü‚«‚É‚µ‚½‚¢‚Ì‚Å‚O“x
		player_rot = 0.0f;
	}
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		player_x -= PLAYER_SPEED;
		//	¶Œü‚«‚Í‚P‚W‚O“x
		player_rot = 180.0f;
	}
	if( CheckHitKey( KEY_INPUT_DOWN ) ){
		player_y += PLAYER_SPEED;
		//	‰ºŒü‚«‚É‚µ‚½‚¢‚Ì‚Å‚X‚O“x
		player_rot = 90.0f;
	}
	if( CheckHitKey( KEY_INPUT_UP ) ){
		player_y -= PLAYER_SPEED;
		//	ãŒü‚«F‚Q‚V‚O“x
//		player_rot = 270.0f;
		//	ãŒü‚«F[‚X‚O“x
		player_rot = -90.0f;
	}

	if (npc_x > SCREEN_W)
	{
		npc_x = 0;
	}
	if (npc_x < 0 )
	{
		npc_x = SCREEN_W;
	}
	if (npc_y > SCREEN_H)
	{
		npc_y = 0;
	}
	if (npc_y < 0)
	{
		npc_y = SCREEN_H;
	}
		
	//	¡‰ñ‚Í‚m‚o‚b‚Ìí‚É‰ñ“]‚Ìˆ—‚Í“ü‚ê‚Ä‚¢‚Ü‚¹‚ñ


	//	ƒvƒŒƒCƒ„[‚Æ‚m‚o‚b‚Å“–‚½‚è”»’èi‰~“¯Žm‚Åj
	if( CheckCircleHit( player_x, player_y, RADIUS, npc_x, npc_y, RADIUS ) ){
		//	“–‚½‚Á‚½‚ç‚m‚o‚b‚ÌÀ•W‚ð‰æ–Ê“à‚Ì‚Ç‚±‚©ƒ‰ƒ“ƒ_ƒ€‚ÉÝ’è
		npc_x = (float)GetRand( SCREEN_W );
		npc_y = (float)GetRand( SCREEN_H );
	}
}
//---------------------------------------------------------------------------------
//	•`‰æˆ—
//---------------------------------------------------------------------------------
void GameRender()
{
	//	À•W‚ÆŒü‚«‚ðÝ’è‚Å‚«‚é•`‰æŠÖ”‚ðŽg‚¢‚Ü‚·

	
	DrawRotaGraphF( npc_x, npc_y, 1.0f, TO_RADIAN( npc_rot ), npc_image, TRUE );

	//	ƒvƒŒƒCƒ„[‚ÌŒü‚« player_roti“xj ‚ðƒ‰ƒWƒAƒ“Šp‚É•ÏŠ· TO_RADIAN ‚µ‚Ä•`‰æŠÖ”‚É“n‚µ‚Ü‚·
	DrawRotaGraphF( player_x, player_y, 1.0f, TO_RADIAN( player_rot ), player_image, TRUE );

	DrawString( 20, 20, "\ŽšƒL[FƒvƒŒƒCƒ„[ˆÚ“®", GetColor( 255, 255, 255 ) );
	DrawString( 20, 40, "‚m‚o‚b‚ÍƒvƒŒƒCƒ„[‚Æ“–‚½‚é‚ÆÀ•WÄÝ’è", GetColor( 255, 255, 255 ) );
	DrawString( 20, 60, "‚m‚o‚b‚Í“K“–‚ÈŽžŠÔ‚½‚Á‚½‚çƒ‰ƒ“ƒ_ƒ€‚ÉŒü‚«‚ð•Ï‚¦‚é", GetColor( 255, 255, 0 ) );
	DrawString( 20, 80, "¨@ã‰º¶‰E‚ÉŒü‚«‚ð•Ï‚¦‚Äã‰º¶‰E‚ÉˆÚ“®", GetColor( 255, 255, 0 ) );
	DrawFormatString(20, 280, GetColor(255, 255, 120), "Facing : %d", npc_facing);
	DrawFormatString(20, 300, GetColor(255, 255, 120), "Facing Timer : %d", facing_timer_rand);

}
//---------------------------------------------------------------------------------
//	I—¹ˆ—
//---------------------------------------------------------------------------------
void GameExit()
{
	//	“Ç‚Ýž‚ñ‚¾‰æ‘œ‚ÌI—¹ˆ—
	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
