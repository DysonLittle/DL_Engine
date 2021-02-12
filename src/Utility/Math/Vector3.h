#pragma once

struct Vector2; // forward declaration for implicit conversion operator overload

struct Vector3
{
	// constructors
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vec); // copy constructor

	// member functions
	void normalize();
	Vector3 normalized();
	float length();
	float squareLength();

	// operator overloads
	Vector3 operator+(const Vector3& rhs);
	Vector3 operator-(const Vector3& rhs);
	Vector3 operator*(const Vector3& rhs);
	Vector3 operator/(const Vector3& rhs);
	bool operator==(const Vector3& rhs);
	operator Vector2() const;

	// static operators
	static float dot(const Vector3& lhs, const Vector3& rhs);
	static Vector3 cross(const Vector3& lhs, const Vector3& rhs);

	// data
	float x, y, z;

	// static values
	static Vector3 ZERO, UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS;
};