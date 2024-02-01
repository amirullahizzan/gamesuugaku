#include "Main.h"
#include "Float2.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Float2::Float2()
{
	x = 0.0f;
	y = 0.0f;
}
Float2::Float2( float x, float y )
{
	this->x = x;
	this->y = y;
}
//---------------------------------------------------------------------------------
//	ゼロ初期化
//---------------------------------------------------------------------------------
void Float2::clear()
{
	x = 0.0f;
	y = 0.0f;
}
//---------------------------------------------------------------------------------
//	値のセット
//---------------------------------------------------------------------------------
void Float2::set( float x, float y )
{
	this->x = x;
	this->y = y;
}
//---------------------------------------------------------------------------------
//	値のセット
//---------------------------------------------------------------------------------
void Float2::set( Float2 &v )
{
	x = v.x;
	y = v.y;
}
//---------------------------------------------------------------------------------
//	長さ取得
//---------------------------------------------------------------------------------
float Float2::GetLength()
{
	return sqrtf( x * x + y * y );
}
//---------------------------------------------------------------------------------
//	正規化（ベクトルの長さを１にする）
//---------------------------------------------------------------------------------
void Float2::normalize()
{
	float length = GetLength();
	if( length > 0.0f ){
		x = x / length;
		y = y / length;
	}
}
//---------------------------------------------------------------------------------
//	長さ設定
//---------------------------------------------------------------------------------
void Float2::SetLength( float length )
{
	normalize();
	x = x * length;
	y = y * length;
}

//---------------------------------------------------------------------------------
//	= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2& Float2::operator = ( const Float2 &v )
{
	x = v.x;
	y = v.y; 
	return *this; 
}
//---------------------------------------------------------------------------------
//	+= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2& Float2::operator += ( const Float2 &v )
{
	x += v.x;
	y += v.y;
	return *this;
}
//---------------------------------------------------------------------------------
//	-= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2& Float2::operator -= ( const Float2 &v )
{
	x -= v.x;
	y -= v.y;
	return *this;
}
//---------------------------------------------------------------------------------
//	*= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2& Float2::operator *= ( const float f )
{
	x *= f;
	y *= f;
	return *this;
}
//---------------------------------------------------------------------------------
//	/= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2& Float2::operator /= ( const float f )
{
	x /= f;
	y /= f;
	return *this;
}

//---------------------------------------------------------------------------------
//	+ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2 operator + ( const Float2 &v1, const Float2 &v2 )
{
	Float2 v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}
//---------------------------------------------------------------------------------
//	- 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2 operator - ( const Float2 &v1, const Float2 &v2 )
{
	Float2 v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}
//---------------------------------------------------------------------------------
//	* 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2 operator * ( const Float2 &v, const float f )
{
	Float2 r;
	r.x = v.x * f;
	r.y = v.y * f;
	return r;
}
//---------------------------------------------------------------------------------
//	/ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float2 operator / ( const Float2 &v, const float f )
{
	Float2 r;
	r.x = v.x / f;
	r.y = v.y / f;
	return r;
}

//---------------------------------------------------------------------------------
//	２つの Float2 の距離を求める
//---------------------------------------------------------------------------------
float GetFloat2Distance( Float2 &pos1, Float2 &pos2 )
{
	Float2 v = pos1 - pos2;
	return v.GetLength();
}
