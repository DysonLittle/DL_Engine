#pragma once

#include <functional>

struct Matrix4;

struct Vector2; // forward declaration for implicit conversion operator overload

struct Vector3
{
private:
	// data
	float vec[3];
public:
	// constructors
	Vector3(float x, float y, float z) : vec{ x, y, z } {}
	Vector3();
	Vector3(float vecArray[3]);
	Vector3(const Vector3& vec); // copy constructor

	// member functions
	void normalize();
	Vector3 normalized();
	float length();
	float squareLength();

	float x() {	return vec[0];	}
	float y() { return vec[1];	}
	float z() { return vec[2];	}

	// operator overloads
	Vector3 operator+(const Vector3& rhs);
	Vector3 operator-(Vector3& rhs);
	Vector3 operator*(Vector3& rhs);
	Vector3 operator/(Vector3& rhs);
	bool operator==(Vector3& rhs);
	float& operator[](int index);
	const float& operator[](int index) const;
	operator Vector2();

	Vector3 operator*(Matrix4& rhs);
	bool operator==(const Vector3& rhs) const;

	// static operators
	static float dot(Vector3 lhs, Vector3 rhs);
	static Vector3 cross(Vector3& lhs, Vector3& rhs);

	// static values
	static Vector3 ZERO, UP, DOWN, LEFT, RIGHT, FORWARDS, BACKWARDS;
};

template<> struct std::hash<Vector3>
{
	size_t operator()(Vector3 const& vector) const
	{
		return ((std::hash<float>()(vector[0]) ^
			(std::hash<float>()(vector[1]) << 1)) >> 1) ^
			(std::hash<float>()(vector[2]) << 1);
	}
};