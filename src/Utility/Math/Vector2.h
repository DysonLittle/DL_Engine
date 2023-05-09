#pragma once

#include <functional>

struct Vector3; // forward declaration for implicit conversion operator overload

struct Vector2
{
	// data
private:
	float vec[2];

public:
	// constructors
	Vector2(float x, float y) : vec{ x, y } {}
	Vector2();
	Vector2(float vec[2]);
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
	bool operator==(const Vector2& rhs) const;
	float operator[](int index) const;
	operator Vector3() const;

	// static operators
	static float dot(const Vector2& lhs, const Vector2& rhs);

	// static values
	static Vector2 ZERO, UP, DOWN, LEFT, RIGHT;
};

template<> struct std::hash<Vector2>
{
	size_t operator()(Vector2 const& vector) const
	{
		return (std::hash<float>()(vector[0]) ^
			(std::hash<float>()(vector[1]) << 1));
	}
};