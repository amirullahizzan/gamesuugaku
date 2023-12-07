#pragma once

//---------------------------------------------------------------------------------
//	Float3 クラス（ x y z があるクラス）
//---------------------------------------------------------------------------------
class Float3
{
public:
	float	x;
	float	y;
	float	z;

	Float3();									//	コンストラクタ
	Float3( float x, float y, float z );

	void clear();								//	ゼロ初期化
	void set( float x, float y, float z );		//	値のセット
	void set( Float3 &v );

	Float3& operator = ( const Float3 &v );		//	= 演算子のオーバーロード

	Float3& operator += ( const Float3 &v );	//	+= 演算子のオーバーロード
	Float3& operator -= ( const Float3 &v );	//	-= 演算子のオーバーロード
	Float3& operator *= ( const float f );		//	*= 演算子のオーバーロード
	Float3& operator /= ( const float f );		//	/= 演算子のオーバーロード
};

//	+ 演算子のオーバーロード
Float3 operator + ( const Float3 &v0, const Float3 &v1 );
//	- 演算子のオーバーロード
Float3 operator - ( const Float3 &v0, const Float3 &v1 );
//	* 演算子のオーバーロード
Float3 operator * ( const Float3 &v, const float f );
//	/ 演算子のオーバーロード
Float3 operator / ( const Float3 &v, const float f );

//	２つの Float3 の距離を求める
float GetFloat3Distance( Float3 &pos1, Float3 &pos2 );
