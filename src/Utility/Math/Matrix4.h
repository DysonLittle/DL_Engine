#pragma once

struct Vector3;
struct Vector4;

struct Matrix4
{
private:
	//data
	float mat[16];

	static float clampZ(float oldZ);
public:
	Matrix4();
	Matrix4(float mat[16]);
	Matrix4(float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float m, float n, float o, float p);

	Matrix4(const Matrix4& rhs);

	float* operator[](int index);
	const float* operator[](int index) const;
	Vector4 column(int index);

	Matrix4 operator*(const Matrix4& rhs) const;

	Matrix4 flipped();

	static Matrix4 axisAngle(Vector3 axis, float angle);
	static Matrix4 lookAt(Vector3 eye, Vector3 at, Vector3 up);
	static Matrix4 project(float angle, float aspect, float near, float far);
	const static Matrix4 IDENTITY;
};