#pragma once

//---------------------------------------------------------------------------------
//	Float2 クラス
//---------------------------------------------------------------------------------
class Float2
{
public:
	float x;
	float y;

	Float2();									//	コンストラクタ
	Float2( float x, float y );

	void clear();								//	ゼロ初期化
	void set( float x, float y );				//	値のセット
	void set( Float2 &v );

	Float2& operator = ( const Float2 &v );		//	= 演算子のオーバーロード

	Float2& operator += ( const Float2 &v );	//	+= 演算子のオーバーロード
	Float2& operator -= ( const Float2 &v );	//	-= 演算子のオーバーロード
	Float2& operator *= ( const float f );		//	*= 演算子のオーバーロード
	Float2& operator /= ( const float f );		//	/= 演算子のオーバーロード
};

//	+ 演算子のオーバーロード
Float2 operator + ( const Float2 &v1, const Float2 &v2 );
//	- 演算子のオーバーロード
Float2 operator - ( const Float2 &v1, const Float2 &v2 );
//	* 演算子のオーバーロード
Float2 operator * ( const Float2 &v, const float f );
//	/ 演算子のオーバーロード
Float2 operator / ( const Float2 &v, const float f );

//	２つの Float2 の距離を求める
float GetFloat2Distance( Float2 &pos1, Float2 &pos2 );
