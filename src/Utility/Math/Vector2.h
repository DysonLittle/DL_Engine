#pragma once

struct Vector3; // forward declaration for implicit conversion operator overload

struct Vector2
{
	// constructors
	Vector2(float x, float y);
	Vector2(const Vector2& vec); // copy constructor

	// member functions
	void normalize();
	Vector2 normalized();
	float length();
	float squareLength();

	// operator overloads
	Vector2 operator+(const Vector2& rhs);
	Vector2 operator-(const Vector2& rhs);
	Vector2 operator*(const Vector2& rhs);
	Vector2 operator/(const Vector2& rhs);
	bool operator==(const Vector2& rhs);
	operator Vector3() const;

	// static operators
	static float dot(const Vector2& lhs, const Vector2& rhs);

	// data
	float x, y;

	// static values
	static Vector2 ZERO, UP, DOWN, LEFT, RIGHT;
};