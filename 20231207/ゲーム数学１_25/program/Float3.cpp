#include "Main.h"
#include "Float3.h"

//---------------------------------------------------------------------------------
//	コンストラクタ
//---------------------------------------------------------------------------------
Float3::Float3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Float3::Float3( float x, float y, float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//---------------------------------------------------------------------------------
//	ゼロ初期化（ＸＹＺの値を０にします）
//---------------------------------------------------------------------------------
void Float3::clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
//---------------------------------------------------------------------------------
//	値のセット（ＸＹＺをそれぞれ受け取るバージョン）
//---------------------------------------------------------------------------------
void Float3::set( float x, float y, float z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}
//---------------------------------------------------------------------------------
//	値のセット（ Float3 を受け取るバージョン ）
//---------------------------------------------------------------------------------
void Float3::set( Float3 &v )
{
	x = v.x;
	y = v.y;
	z = v.z;
}

//---------------------------------------------------------------------------------
//	= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3& Float3::operator = ( const Float3 &v )
{
	x = v.x;
	y = v.y; 
	z = v.z; 
	return *this; 
}
//---------------------------------------------------------------------------------
//	+= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3& Float3::operator += ( const Float3 &v )
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	-= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3& Float3::operator -= ( const Float3 &v )
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
//---------------------------------------------------------------------------------
//	*= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3& Float3::operator *= ( const float f )
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
//---------------------------------------------------------------------------------
//	/= 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3& Float3::operator /= ( const float f )
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

//---------------------------------------------------------------------------------
//	+ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3 operator + ( const Float3 &v0, const Float3 &v1 )
{
	Float3 v;
	v.x = v0.x + v1.x;
	v.y = v0.y + v1.y;
	v.z = v0.z + v1.z;
	return v;
}
//---------------------------------------------------------------------------------
//	- 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3 operator - ( const Float3 &v0, const Float3 &v1 )
{
	Float3 v;
	v.x = v0.x - v1.x;
	v.y = v0.y - v1.y;
	v.z = v0.z - v1.z;
	return v;
}
//---------------------------------------------------------------------------------
//	* 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3 operator * ( const Float3 &v, const float f )
{
	Float3 r;
	r.x = v.x * f;
	r.y = v.y * f;
	r.z = v.z * f;
	return r;
}
//---------------------------------------------------------------------------------
//	/ 演算子のオーバーロード
//---------------------------------------------------------------------------------
Float3 operator / ( const Float3 &v, const float f )
{
	Float3 r;
	r.x = v.x / f;
	r.y = v.y / f;
	r.z = v.z / f;
	return r;
}

//---------------------------------------------------------------------------------
//	２つの Float3 の距離を求める
//---------------------------------------------------------------------------------
float GetFloat3Distance( Float3 &pos1, Float3 &pos2 )
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float z = pos1.z - pos2.z;
	float distance = sqrtf( x * x + y * y + z * z );
	return distance;
}
