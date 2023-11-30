#pragma once

//---------------------------------------------------------------------------------
//	Float3 �N���X�i x y z ������N���X�j
//---------------------------------------------------------------------------------
class Float3
{
public:
	float	x;
	float	y;
	float	z;

	Float3();									//	�R���X�g���N�^
	void clear();								//	�[��������
	void set( float x, float y, float z );		//	�l�̃Z�b�g
	void set( Float3 v );
};

float GetFloat3Distance( Float3 pos1, Float3 pos2 );
