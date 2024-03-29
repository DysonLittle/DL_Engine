#include "Quaternion.h"
#include "Vector3.h"
#include <cmath>

Quaternion::Quaternion(float x, float y, float z, float w)
{
}

Quaternion::Quaternion(Vector3 eulerRotation)
{
}

Vector3 Quaternion::getXYZ()
{
	return Vector3::ZERO;
}

Quaternion Quaternion::inverse()
{
	return Quaternion(-this->x, -this->y, -this->z, this->w);
}

Vector3 Quaternion::operator*(const Vector3& rhs)
{
	return Vector3::ZERO; //TODO
}

Quaternion Quaternion::operator*(const Quaternion& rhs)
{
	// Hamilton Product
	float outX, outY, outZ, outW;

	outW = this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z;
	outX = this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y;
	outY = this->w * rhs.y - this->x * rhs.z + this->y * rhs.w + this->z * rhs.x;
	outZ = this->w * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.w;

	return Quaternion(outX, outY, outZ, outW);
}

Quaternion Quaternion::eulerAngle(Vector3 eulerAngle)
{
	float cosX = cos(eulerAngle[0] * 0.5f);
	float cosY = cos(eulerAngle[1] * 0.5f);
	float cosZ = cos(eulerAngle[2] * 0.5f);
	float sinX = sin(eulerAngle[0] * 0.5f);
	float sinY = sin(eulerAngle[1] * 0.5f);
	float sinZ = sin(eulerAngle[2] * 0.5f);

	float outW = cosX * cosY * cosZ + sinX * sinY * sinZ;
	float outX = sinX * cosY * cosZ - cosX * sinY * sinZ;
	float outY = cosX * sinY * cosZ + sinX * cosY * sinZ;
	float outZ = cosX * cosY * sinZ - sinX * sinY * cosZ;

	return Quaternion(outX, outY, outZ, outW);
}

void Quaternion::normalize()
{
}
