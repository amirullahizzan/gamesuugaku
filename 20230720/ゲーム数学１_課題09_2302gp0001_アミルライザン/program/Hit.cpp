#include "Main.h"
#include "Game.h"

//---------------------------------------------------------------------------------
//	２点の長さを取得する関数
//---------------------------------------------------------------------------------
float GetDistance( float x1, float y1, float x2, float y2 )
{
	float x = x1 - x2;
	float y = y1 - y2;
	float d = sqrtf( x * x + y * y );
	return d;
}

//---------------------------------------------------------------------------------
//	円同士の当たり判定
//		x1：円１のＸ座標
//		y1：円１のＹ座標
//		r1：円１の半径
//		x2：円２のＸ座標
//		y2：円２のＹ座標
//		r2：円２の半径
//	当たっていたら true を、当たっていなかったら false を返す
//---------------------------------------------------------------------------------
bool CheckCircleHit( float x1, float y1, float r1, float x2, float y2, float r2 )
{
	//	１：２つの円の座標の距離を求める
	float distance = GetDistance( x1, y1, x2, y2 );
	//	２：半径の合計を求める
	float radius = r1 + r2;
	//	３：２点の距離が半径の合計以下だったら当たっている
	if( distance <= radius ){
		//	当たっていたら true を返す
		//	return：これが呼ばれた時点でこの関数は終了、なのでこの下の処理は呼ばれない
		return true;
	}
	//	じゃなかったら false を返す
	return false;
}
//---------------------------------------------------------------------------------
//	点と円の当たり判定
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
//	四角同士の当たり判定
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
//	点と四角の当たり判定
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
