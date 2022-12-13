#pragma once


struct Matrix4
{
	//data
	float mat[16];


	Matrix4(float mat[16]);
	Matrix4(const Matrix4& mat);

	float* operator[](int index);
};