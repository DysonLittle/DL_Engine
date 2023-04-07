#include "Vector3.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Vector4.h"
#include <cmath>
#pragma once

Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Vector3::UP = Vector3(0.0f, 1.0f, 0.0f);
Vector3 Vector3::DOWN = Vector3(0.0f, -1.0f, 0.0f);
Vector3 Vector3::LEFT = Vector3(-1.0f, 0.0f, 0.0f);
Vector3 Vector3::RIGHT = Vector3(1.0f, 0.0f, 0.0f);
Vector3 Vector3::FORWARDS = Vector3(0.0f, 0.0f, 1.0f);
Vector3 Vector3::BACKWARDS = Vector3(0.0f, 0.0f, -1.0f);

/// <summary>
/// Default Vector3 constructor. Assigns every value to zero.
/// </summary>
/// <returns>Constructed Vector3.</returns>
Vector3::Vector3()
{
	for (int i = 0; i < 3; ++i)
	{
		vec[i] = 0.0f;
	}
}

/// <summary>
/// Array Vector3 constructor.
/// </summary>
/// <param name="vecArray">Float array containing vector.</param>
/// <returns>Constructed Vector3.</returns>
Vector3::Vector3(float vecArray[3])
{
	for (int i = 0; i < 3; ++i)
	{
		vec[i] = vecArray[i];
	}
}

/// <summary>
/// Standard Vector3 constructor.
/// </summary>
/// <param name="x">X element of Vector.</param>
/// <param name="y">Y element of Vector.</param>
/// <param name="z">Z element of Vector.</param>
/// <returns>Constructed Vector3.</returns>
//Vector3::Vector3(float x, float y, float z)
//{
//	this->vec[0] = x;
//	this->vec[1] = y;
//	this->vec[2] = z;
//}

/// <summary>
/// Vector3 copy constructor.
/// </summary>
/// <param name="vec">Vector to be copied.</param>
/// <returns>Constructed Vector3.</returns>
Vector3::Vector3(const Vector3& vec)
{
	this->vec[0] = vec[0];
	this->vec[1] = vec[1];
	this->vec[2] = vec[2];
}

/// <summary>
/// Normalizes the Vector3.
/// </summary>
void Vector3::normalize()
{
	float hypotenuse = this->length();
	this->vec[0] /= hypotenuse;
	this->vec[1] /= hypotenuse;
	this->vec[2] /= hypotenuse;
}

/// <summary>
/// Returns a normalized version of the Vector3.
/// </summary>
/// <returns>Normalized Vector3.</returns>
Vector3 Vector3::normalized()
{
	float hypotenuse = this->length();
	return Vector3(this->vec[0] / hypotenuse, this->vec[1] / hypotenuse, this->vec[2] / hypotenuse);
}

/// <summary>
/// Returns the length of the Vector3.
/// </summary>
/// <returns>Vector3 length as a float.</returns>
float Vector3::length()
{
	// Pythagorean theorem
	return sqrt(this->squareLength());
}

/// <summary>
/// Returns the length of the Vector3 squared. This method is more efficient than Vector3::length() and should be used when possible.
/// </summary>
/// <returns>Vector3 square length as a float.</returns>
float Vector3::squareLength()
{
	// Pythagorean theorem without sqrt
	return (vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2]);
}

/// <summary>
/// + operator overload. Sums the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be summed with this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator+(const Vector3& rhs)
{
	return Vector3(this->vec[0] + rhs[0], this->vec[1] + rhs[1], this->vec[2] + rhs[2]);
}

/// <summary>
/// - operator overload. Subtracts the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be subtracted from this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator-(Vector3& rhs)
{
	return Vector3(this->vec[0] - rhs[0], this->vec[1] - rhs[1], this->vec[2] - rhs[2]);
}

/// <summary>
/// * operator overload. Multiplies the Vector3s element-wise. For dot product, use Vector3::dot(), and for cross product, use Vector3::cross().
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be multiplied with this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator*(Vector3& rhs)
{
	return Vector3(this->vec[0] * rhs[0], this->vec[1] * rhs[1], this->vec[2] * rhs[2]);
}

/// <summary>
/// / operator overload. Divides the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to divide this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator/(Vector3& rhs)
{
	return Vector3(this->vec[0] / rhs[0], this->vec[1] / rhs[1], this->vec[2] / rhs[2]);
}

/// <summary>
/// == operator overload. Compares the Vector3s element-wise for equality.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be compared to this.</param>
/// <returns>Boolean based on element-wise equality.</returns>
bool Vector3::operator==(Vector3& rhs)
{
	return this->vec[0] == rhs[0] && this->vec[1] == rhs[1] && this->vec[2] == rhs[2];
}

/// <summary>
/// [] operator to get vector float elements.
/// </summary>
/// <param name="index">Index of float to return.</param>
/// <returns>Float at index.</returns>
float& Vector3::operator[](int index)
{
	return vec[index];
}

/// <summary>
/// [] operator to get vector float elements.
/// </summary>
/// <param name="index">Index of float to return.</param>
/// <returns>Float at index.</returns>
const float& Vector3::operator[](int index) const
{
	return vec[index];
}

/// <summary>
/// Explicit cast to Vector2 operator overload. Copies the x and y values, and discards the z value.
/// </summary>
/// <returns>Resulting Vector2.</returns>
Vector3::operator Vector2()
{
	// Discard z value
	return Vector2(this->vec[0], this->vec[1]);
}

/// <summary>
/// * operator to multiply vector by matrix4.
/// </summary>
/// <param name="rhs">Matrix4 to multiply.</param>
/// <returns>Transformed Vector3.</returns>
Vector3 Vector3::operator*(Matrix4& rhs)
{
	// translate first
	Vector3 translatedVec = *this + Vector3(rhs.column(3));

	// then rotate and shear and scale
	Vector3 newVec;

	for (int i = 0; i < 3; ++i)
	{
		float sum = 0.0f;
		for (int j = 0; j < 3; ++j)
		{
			sum += rhs[i][j] * vec[j];
		}
		newVec[i] = sum;
	}

	return newVec;
}

/// <summary>
/// Dot operator. Performs the dot operation on two Vector3s.
/// </summary>
/// <param name="lhs">The left hand side Vector3 to be dotted.</param>
/// <param name="rhs">The right hand side Vector3 to be dotted.</param>
/// <returns>Resulting scalar, as a float.</returns>
float Vector3::dot(Vector3 lhs, Vector3 rhs)
{
	return (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]);
}

/// <summary>
/// Cross operator. Performs the cross operation on two Vector3s.
/// </summary>
/// <param name="lhs">The left hand side Vector3 to be crossed.</param>
/// <param name="rhs">The right hand side Vector3 to be crossed.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::cross(Vector3& lhs, Vector3& rhs)
{
	return Vector3(	lhs[1] * rhs[2] - lhs[2] * rhs[1],
					lhs[2] * rhs[0] - lhs[0] * rhs[2],
					lhs[0] * rhs[1] - lhs[1] * rhs[0]);
}