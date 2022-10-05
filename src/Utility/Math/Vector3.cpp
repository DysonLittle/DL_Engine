#include "Vector3.h"
#include "Vector2.h"
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
/// Standard Vector3 constructor.
/// </summary>
/// <param name="x">X element of Vector.</param>
/// <param name="y">Y element of Vector.</param>
/// <param name="z">Z element of Vector.</param>
/// <returns>Constructed Vector3.</returns>
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

/// <summary>
/// Vector3 copy constructor.
/// </summary>
/// <param name="vec">Vector to be copied.</param>
/// <returns>Constructed Vector3.</returns>
Vector3::Vector3(const Vector3& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

/// <summary>
/// Normalizes the Vector3.
/// </summary>
void Vector3::normalize()
{
	float hypotenuse = this->length();
	this->x /= hypotenuse;
	this->y /= hypotenuse;
	this->z /= hypotenuse;
}

/// <summary>
/// Returns a normalized version of the Vector3.
/// </summary>
/// <returns>Normalized Vector3.</returns>
Vector3 Vector3::normalized()
{
	float hypotenuse = this->length();
	return Vector3(this->x / hypotenuse, this->y / hypotenuse, this->z / hypotenuse);
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
	return x * x + y * y + z * z;
}

/// <summary>
/// + operator overload. Sums the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be summed with this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator+(const Vector3& rhs)
{
	return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

/// <summary>
/// - operator overload. Subtracts the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be subtracted from this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator-(const Vector3& rhs)
{
	return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}

/// <summary>
/// * operator overload. Multiplies the Vector3s element-wise. For dot product, use Vector3::dot(), and for cross product, use Vector3::cross().
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be multiplied with this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator*(const Vector3& rhs)
{
	return Vector3(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
}

/// <summary>
/// / operator overload. Divides the Vector3s element-wise.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to divide this.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::operator/(const Vector3& rhs)
{
	return Vector3(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
}

/// <summary>
/// == operator overload. Compares the Vector3s element-wise for equality.
/// </summary>
/// <param name="rhs">The right hand side Vector3 to be compared to this.</param>
/// <returns>Boolean based on element-wise equality.</returns>
bool Vector3::operator==(const Vector3& rhs)
{
	return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
}

/// <summary>
/// Explicit cast to Vector2 operator overload. Copies the x and y values, and discards the z value.
/// </summary>
/// <returns>Resulting Vector2.</returns>
Vector3::operator Vector2() const
{
	// Discard z value
	return Vector2(this->x, this->y);
}

/// <summary>
/// Dot operator. Performs the dot operation on two Vector3s.
/// </summary>
/// <param name="lhs">The left hand side Vector3 to be dotted.</param>
/// <param name="rhs">The right hand side Vector3 to be dotted.</param>
/// <returns>Resulting scalar, as a float.</returns>
float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

/// <summary>
/// Cross operator. Performs the cross operation on two Vector3s.
/// </summary>
/// <param name="lhs">The left hand side Vector3 to be crossed.</param>
/// <param name="rhs">The right hand side Vector3 to be crossed.</param>
/// <returns>Resulting Vector3.</returns>
Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(	lhs.y * rhs.z - lhs.z * rhs.y,
					lhs.z * rhs.x - lhs.x * rhs.z,
					lhs.x * rhs.y - lhs.y * rhs.x);
}