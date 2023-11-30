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
	void clear();								//	ゼロ初期化
	void set( float x, float y, float z );		//	値のセット
	void set( Float3 v );
};

float GetFloat3Distance( Float3 pos1, Float3 pos2 );
