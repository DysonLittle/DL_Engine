#pragma once

struct Vector3;

struct Vector4 {
private:
	float vec[4];
public:
	Vector4();
	Vector4(float x, float y, float z, float q);
	Vector4(float vec[4]);

	float& operator[](int index);
	const float& operator[](int index) const;

	operator Vector3();
};