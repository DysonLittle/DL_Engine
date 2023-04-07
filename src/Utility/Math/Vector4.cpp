#include "Vector4.h"
#include "Vector3.h"

Vector4::Vector4()
{
	for (int i = 0; i < 4; i++)
	{
		vec[i] = 0.0f;
	}
}

Vector4::Vector4(float x, float y, float z, float q)
{
	this->vec[0] = x;
	this->vec[1] = y;
	this->vec[2] = z;
	this->vec[3] = q;
}

Vector4::Vector4(float vec[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->vec[i] = vec[i];
	}
}

float& Vector4::operator[](int index)
{
	return this->vec[index];
}

const float& Vector4::operator[](int index) const
{
	return this->vec[index];
}

Vector4::operator Vector3()
{
	// truncate
	return Vector3(vec[0], vec[1], vec[2]);
}
