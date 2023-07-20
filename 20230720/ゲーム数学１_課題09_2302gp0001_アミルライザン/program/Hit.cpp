#include "Main.h"
#include "Game.h"

//---------------------------------------------------------------------------------
//	‚Q“_‚Ì’·‚³‚ğæ“¾‚·‚éŠÖ”
//---------------------------------------------------------------------------------
float GetDistance( float x1, float y1, float x2, float y2 )
{
	float x = x1 - x2;
	float y = y1 - y2;
	float d = sqrtf( x * x + y * y );
	return d;
}

//---------------------------------------------------------------------------------
//	‰~“¯m‚Ì“–‚½‚è”»’è
//		x1F‰~‚P‚Ì‚wÀ•W
//		y1F‰~‚P‚Ì‚xÀ•W
//		r1F‰~‚P‚Ì”¼Œa
//		x2F‰~‚Q‚Ì‚wÀ•W
//		y2F‰~‚Q‚Ì‚xÀ•W
//		r2F‰~‚Q‚Ì”¼Œa
//	“–‚½‚Á‚Ä‚¢‚½‚ç true ‚ğA“–‚½‚Á‚Ä‚¢‚È‚©‚Á‚½‚ç false ‚ğ•Ô‚·
//---------------------------------------------------------------------------------
bool CheckCircleHit( float x1, float y1, float r1, float x2, float y2, float r2 )
{
	//	‚PF‚Q‚Â‚Ì‰~‚ÌÀ•W‚Ì‹——£‚ğ‹‚ß‚é
	float distance = GetDistance( x1, y1, x2, y2 );
	//	‚QF”¼Œa‚Ì‡Œv‚ğ‹‚ß‚é
	float radius = r1 + r2;
	//	‚RF‚Q“_‚Ì‹——£‚ª”¼Œa‚Ì‡ŒvˆÈ‰º‚¾‚Á‚½‚ç“–‚½‚Á‚Ä‚¢‚é
	if( distance <= radius ){
		//	“–‚½‚Á‚Ä‚¢‚½‚ç true ‚ğ•Ô‚·
		//	returnF‚±‚ê‚ªŒÄ‚Î‚ê‚½“_‚Å‚±‚ÌŠÖ”‚ÍI—¹A‚È‚Ì‚Å‚±‚Ì‰º‚Ìˆ—‚ÍŒÄ‚Î‚ê‚È‚¢
		return true;
	}
	//	‚¶‚á‚È‚©‚Á‚½‚ç false ‚ğ•Ô‚·
	return false;
}
//---------------------------------------------------------------------------------
//	“_‚Æ‰~‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckPointCircleHit( float point_x, float point_y, float circle_x, float circle_y, float circle_r )
{
	float distance = GetDistance( point_x, point_y, circle_x, circle_y );
	if( distance <= circle_r ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	lŠp“¯m‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckBoxHit( float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2 )
{
	if( x1 + w1 >= x2 && x1 <= x2 + w2 ){
		if( y1 + h1 >= y2 && y1 <= y2 + h2 ){
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	“_‚ÆlŠp‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckPointBoxHit( float point_x, float point_y, float box_x, float box_y, float box_w, float box_h )
{
	if( point_x >= box_x && point_x <= box_x + box_w ){
		if( point_y >= box_y && point_y <= box_y + box_h ){
			return true;
		}
	}
	return false;
}
