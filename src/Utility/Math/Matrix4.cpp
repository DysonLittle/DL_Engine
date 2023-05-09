#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <stdexcept>
#include <cmath>
#pragma once

const Matrix4 Matrix4::IDENTITY = { 1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 1.0f };


float Matrix4::clampZ(float oldZ)
{
	return (oldZ / 2.0f) + 0.5f;
}

Matrix4::Matrix4()
{
	//init with identity
	for (int i = 0; i < 16; ++i)
	{
		if ((i % 4) == (i / 4))
			this->mat[i] = 1.0f;
		else
			this->mat[i] = 0.0f;
	}
}

/// <summary>
/// Array Constructor.
/// </summary>
/// <param name="mat">A 16-element array containing the Matrix4.</param>
/// <returns>Constructed Matrix4.</returns>
Matrix4::Matrix4(float mat[16])
{
	for (int i = 0; i < 16; ++i)
	{
		this->mat[i] = mat[i];
	}
}

/// <summary>
/// Individual element constructor.
/// </summary>
/// <param name="a">Element a.</param>
/// <param name="b">Element b.</param>
/// <returns>Constructed Matrix4.</returns>
Matrix4::Matrix4(float a, float b, float c, float d,
	float e, float f, float g, float h,
	float i, float j, float k, float l,
	float m, float n, float o, float p)
{
	mat[0] = a;
	mat[1] = b;
	mat[2] = c;
	mat[3] = d;
	mat[4] = e;
	mat[5] = f;
	mat[6] = g;
	mat[7] = h;
	mat[8] = i;
	mat[9] = j;
	mat[10] = k;
	mat[11] = l;
	mat[12] = m;
	mat[13] = n;
	mat[14] = o;
	mat[15] = p;
}


/// <summary>
/// Copy constructor.
/// </summary>
/// <param name="rhs">Matrix to copy.</param>
/// <returns>Constructed Matrix4.</returns>
Matrix4::Matrix4(const Matrix4& rhs)
{
	for (int i = 0; i < 16; ++i)
	{
		mat[i] = rhs.mat[i];
	}
}


/// <summary>
/// [] operator to get matrix rows.
/// </summary>
/// <param name="index">Row to return.</param>
/// <returns>Row, as a pointer to a float array.</returns>
float* Matrix4::operator[](int index)
{
	if (index >= 4)
		throw std::runtime_error("Matrix index out of range!");
	return &(mat[index * 4]);
}

/// <summary>
/// Const version of [] operator to get matrix rows.
/// </summary>
/// <param name="index">Row to return.</param>
/// <returns>Row, as a float array.</returns>
const float* Matrix4::operator[](int index) const
{
	if (index >= 4)
		throw std::runtime_error("Matrix index out of range!");
	return &(mat[index * 4]);
}

/// <summary>
/// Get matrix columns.
/// </summary>
/// <param name="index">Column to return.</param>
/// <returns>Column, as a float array.</returns>
Vector4 Matrix4::column(int index)
{
	Vector4 returnVec{};

	for (int i = 0; i < 4; ++i)
	{
		returnVec[i] = mat[(i * 4) + index];
	}
	return returnVec;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
	// from https://en.wikipedia.org/wiki/Matrix_multiplication#:~:text=In%20mathematics%2C%20particularly%20in%20linear,rows%20in%20the%20second%20matrix.

	Matrix4 returnMat{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			returnMat[i][j] =	(mat[(i * 4) + 0] * rhs[0][j]) +
								(mat[(i * 4) + 1] * rhs[1][j]) +
								(mat[(i * 4) + 2] * rhs[2][j]) +
								(mat[(i * 4) + 3] * rhs[3][j]);
		}
	}

	return returnMat;
}

Matrix4 Matrix4::flipped()
{
	Matrix4 returnMatrix{};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			returnMatrix[i][j] = mat[(j * 4) + i];
		}
	}

	return returnMatrix;
}

Matrix4 Matrix4::axisAngle(Vector3 axis, float angle)
{
	//from https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle

	float returnArray[16];

	Vector3 v = axis.normalized();
	float s = sin(angle);
	float c = cos(angle);
	float x = v.x();
	float y = v.y();
	float z = v.z();

	returnArray[0] = c + (x * x * (1.0f - c));
	returnArray[1] = (x * y * (1.0f - c)) - (z * s);
	returnArray[2] = (x * z * (1.0f - c)) + (y * s);
	returnArray[3] = 0.0f;
	returnArray[4] = (y * x * (1.0f - c)) + (z * s);
	returnArray[5] = c + (y * y * (1.0f - c));
	returnArray[6] = (y * z * (1.0f - c)) - (x * s);
	returnArray[7] = 0.0f;
	returnArray[8] = (z * x * (1.0f - c)) - (y * s);
	returnArray[9] = (z * y * (1.0f - c)) + (x * s);
	returnArray[10] = c + (z * z * (1.0f - c));
	returnArray[11] = 0.0f;
	returnArray[12] = 0.0f;
	returnArray[13] = 0.0f;
	returnArray[14] = 0.0f;
	returnArray[15] = 1.0f;

	return Matrix4(returnArray);
}

Matrix4 Matrix4::lookAt(Vector3 eye, Vector3 at, Vector3 up)
{
	//from https://stackoverflow.com/questions/349050/calculating-a-lookat-matrix#:~:text=The%20lookat%20matrix%20is%20a,from%20another%20point%20in%20space.
	//then it didn't work so I tried
	// https://www.scratchapixel.com/lessons/mathematics-physics-for-computer-graphics/lookat-function/framing-lookat-function.html
	// and then later that had a bug which I fixed by consulting
	// https://github.com/Lephar/Engine

	float returnArray[16];

	Vector3 forward = (at - eye).normalized();
	Vector3 right = (Vector3::cross(forward, up)).normalized();
	Vector3 newUp = Vector3::cross(right, forward);

	returnArray[0] = right.x();
	returnArray[1] = newUp.x();
	returnArray[2] = -forward.x();
	returnArray[3] = 0.0f;
	returnArray[4] = right.y();
	returnArray[5] = newUp.y();
	returnArray[6] = -forward.y();
	returnArray[7] = 0.0f;
	returnArray[8] = right.z();
	returnArray[9] = newUp.z();
	returnArray[10] = -forward.z();
	returnArray[11] = 0.0f;
	returnArray[12] = -Vector3::dot(right, eye);
	returnArray[13] = -Vector3::dot(newUp, eye);
	returnArray[14] = Vector3::dot(forward, eye);
	returnArray[15] = 1.0f;

	return Matrix4(returnArray);
}

Matrix4 Matrix4::project(float angle, float aspect, float near, float far)
{
	// this went through a lot of iterations but the code that eventually worked was based off of code found here https://vincent-p.github.io/posts/vulkan_perspective_matrix/
	// edit: I had to change it with code from https://github.com/Lephar/Engine

	float focal_length = 1.0f / tan(angle * 0.5f);

	return Matrix4{
		focal_length / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, -focal_length, 0.0f, 0.0f,
		0.0f, 0.0f, -far / (far - near), -1.0f,
		0.0f, 0.0f, -(near * far) / (far - near), 0.0f
	};
}
