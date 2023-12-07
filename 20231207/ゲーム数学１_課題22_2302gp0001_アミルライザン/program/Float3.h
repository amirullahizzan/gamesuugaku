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
	Float3( float x, float y, float z );

	void clear();								//	�[��������
	void set( float x, float y, float z );		//	�l�̃Z�b�g
	void set( Float3 &v );

	Float3& operator = ( const Float3 &v );		//	= ���Z�q�̃I�[�o�[���[�h

	Float3& operator += ( const Float3 &v );	//	+= ���Z�q�̃I�[�o�[���[�h
	Float3& operator -= ( const Float3 &v );	//	-= ���Z�q�̃I�[�o�[���[�h
	Float3& operator *= ( const float f );		//	*= ���Z�q�̃I�[�o�[���[�h
	Float3& operator /= ( const float f );		//	/= ���Z�q�̃I�[�o�[���[�h
};

//	+ ���Z�q�̃I�[�o�[���[�h
Float3 operator + ( const Float3 &v0, const Float3 &v1 );
//	- ���Z�q�̃I�[�o�[���[�h
Float3 operator - ( const Float3 &v0, const Float3 &v1 );
//	* ���Z�q�̃I�[�o�[���[�h
Float3 operator * ( const Float3 &v, const float f );
//	/ ���Z�q�̃I�[�o�[���[�h
Float3 operator / ( const Float3 &v, const float f );

//	�Q�� Float3 �̋��������߂�
float GetFloat3Distance( Float3 &pos1, Float3 &pos2 );
