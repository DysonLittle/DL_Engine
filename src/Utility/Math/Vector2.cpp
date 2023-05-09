#include "Vector2.h"
#include "Vector3.h"
#include <cmath>

#pragma once

Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);
Vector2 Vector2::UP = Vector2(0.0f, 1.0f);
Vector2 Vector2::DOWN = Vector2(0.0f, -1.0f);
Vector2 Vector2::LEFT = Vector2(-1.0f, 0.0f);
Vector2 Vector2::RIGHT = Vector2(1.0f, 0.0f);



/// <summary>
/// Default Vector2 constructor. Assigns every value to zero.
/// </summary>
/// <returns>Constructed Vector2.</returns>
Vector2::Vector2()
{
	vec[0] = 0.0f;
	vec[1] = 0.0f;
}

/// <summary>
/// Standard Vector2 constructor.
/// </summary>
/// <param name="x">X element of Vector.</param>
/// <param name="y">Y element of Vector.</param>
/// <returns>Constructed Vector2.</returns>
//Vector2::Vector2(float x, float y)
//{
//	this->vec[0] = x;
//	this->vec[1] = y;
//}


/// <summary>
/// Array Vector2 constructor.
/// </summary>
/// <param name="vec">Float array containing vector.</param>
/// <returns>Constructed Vector2.</returns>
Vector2::Vector2(float vec[2])
{
	for (int i = 0; i < 2; ++i)
	{
		this->vec[i] = vec[i];
	}
}

/// <summary>
/// Vector2 copy constructor.
/// </summary>
/// <param name="vec">Vector to be copied.</param>
/// <returns>Constructed Vector2.</returns>
Vector2::Vector2(const Vector2& vec)
{
	for (int i = 0; i < 2; ++i)
	{
		this->vec[i] = vec[i];
	}
}

/// <summary>
/// Normalizes the Vector2.
/// </summary>
void Vector2::normalize()
{
	float hypotenuse = this->length();
	this->vec[0] /= hypotenuse;
	this->vec[1] /= hypotenuse;
}

/// <summary>
/// Returns a normalized version of the Vector2.
/// </summary>
/// <returns>Normalized Vector2.</returns>
Vector2 Vector2::normalized()
{
	float hypotenuse = this->length();
	return Vector2(this->vec[0] / hypotenuse, this->vec[1] / hypotenuse);
}

/// <summary>
/// Returns the length of the Vector2.
/// </summary>
/// <returns>Vector2 length as a float.</returns>
float Vector2::length()
{
	// Pythagorean theorem
	return sqrt(this->squareLength());
}

/// <summary>
/// Returns the length of the Vector2 squared. This method is more efficient than Vector2::length() and should be used when possible.
/// </summary>
/// <returns>Vector2 square length as a float.</returns>
float Vector2::squareLength()
{
	// Pythagorean theorem without sqrt
	return vec[0] * vec[0] + vec[1] * vec[1];
}

/// <summary>
/// + operator overload. Sums the Vector2s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector2 to be summed with this.</param>
/// <returns>Resulting Vector2.</returns>
Vector2 Vector2::operator+(const Vector2& rhs)
{
	return Vector2(this->vec[0] + rhs[0], this->vec[1] + rhs[1]);
}

/// <summary>
/// - operator overload. Subtracts the Vector2s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector2 to be subtracted from this.</param>
/// <returns>Resulting Vector2.</returns>
Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(this->vec[0] - rhs[0], this->vec[1] - rhs[1]);
}

/// <summary>
/// * operator overload. Multiplies the Vector2s element-wise. For dot product, use Vector2::dot().
/// </summary>
/// <param name="rhs">The right hand side Vector2 to be multiplied with this.</param>
/// <returns>Resulting Vector2.</returns>
Vector2 Vector2::operator*(const Vector2& rhs)
{
	return Vector2(this->vec[0] * rhs[0], this->vec[1] * rhs[1]);
}

/// <summary>
/// / operator overload. Divides the Vector2s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector2 to divide this.</param>
/// <returns>Resulting Vector2.</returns>
Vector2 Vector2::operator/(const Vector2& rhs)
{
	return Vector2(this->vec[0] / rhs[0], this->vec[1] / rhs[1]);
}

/// <summary>
/// == operator overload. Compares the Vector2s element-wise for equality.
/// </summary>
/// <param name="rhs">The right hand side Vector2 to be compared to this.</param>
/// <returns>Boolean based on element-wise equality.</returns>
bool Vector2::operator==(const Vector2& rhs) const
{
	return this->vec[0] == rhs[0] && this->vec[1] == rhs[1];
}

float Vector2::operator[](int index) const
{
	return vec[index];
}

/// <summary>
/// Explicit cast to Vector3 operator overload. Copies the x and y values, and adds a z value of 0f.
/// </summary>
/// <returns>Resulting Vector3.</returns>
Vector2::operator Vector3() const
{
	// Assume z value is zero
	return Vector3(this->vec[0], this->vec[1], 0.0f);
}

/// <summary>
/// Dot operator. Performs the dot operation on two Vector2s.
/// </summary>
/// <param name="lhs">The left hand side Vector2 to be dotted.</param>
/// <param name="rhs">The right hand side Vector2 to be dotted.</param>
/// <returns>Resulting scalar, as a float.</returns>
float Vector2::dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1];
}
