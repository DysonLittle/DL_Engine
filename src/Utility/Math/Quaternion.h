#pragma once

struct Vector3;

struct Quaternion
{
	//constructors
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 eulerRotation);

	//why doesn't c++ have computed values?
	Vector3 getXYZ();

	Quaternion inverse();

	//operator overloads
	Vector3 operator*(const Vector3& rhs);
	Quaternion operator*(const Quaternion& rhs);

	//data
	float x, y, z, w;

	//static functions, mostly creating Quaternions
	static Quaternion eulerAngle(Vector3 eulerAngle);

private:
	void normalize();


};