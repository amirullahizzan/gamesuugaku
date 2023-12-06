#pragma once

//---------------------------------------------------------------------------------
//	Float2 �N���X
//---------------------------------------------------------------------------------
class Float2
{
public:
	float x;
	float y;

	Float2();									//	�R���X�g���N�^
	Float2( float x, float y );

	void clear();								//	�[��������
	void set( float x, float y );				//	�l�̃Z�b�g
	void set( Float2 &v );

	Float2& operator = ( const Float2 &v );		//	= ���Z�q�̃I�[�o�[���[�h

	Float2& operator += ( const Float2 &v );	//	+= ���Z�q�̃I�[�o�[���[�h
	Float2& operator -= ( const Float2 &v );	//	-= ���Z�q�̃I�[�o�[���[�h
	Float2& operator *= ( const float f );		//	*= ���Z�q�̃I�[�o�[���[�h
	Float2& operator /= ( const float f );		//	/= ���Z�q�̃I�[�o�[���[�h
};

//	+ ���Z�q�̃I�[�o�[���[�h
Float2 operator + ( const Float2 &v1, const Float2 &v2 );
//	- ���Z�q�̃I�[�o�[���[�h
Float2 operator - ( const Float2 &v1, const Float2 &v2 );
//	* ���Z�q�̃I�[�o�[���[�h
Float2 operator * ( const Float2 &v, const float f );
//	/ ���Z�q�̃I�[�o�[���[�h
Float2 operator / ( const Float2 &v, const float f );

//	�Q�� Float2 �̋��������߂�
float GetFloat2Distance( Float2 &pos1, Float2 &pos2 );
