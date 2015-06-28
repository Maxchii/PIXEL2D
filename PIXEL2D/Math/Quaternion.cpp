#include "Quaternion.h"

namespace PIXL { namespace math{

	Quaternion::Quaternion()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

	Quaternion::Quaternion(Float32 w, Float32 x, Float32 y, Float32 z)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Quaternion::Set(const Float32& x, const Float32& y, const Float32& z, const Float32& w)
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Quaternion::Angle(const Quaternion& a, const Quaternion& b)
	{
		return 0;
	}

	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}

	Quaternion Quaternion::Inverse(const Quaternion& rotation)
	{
		return Quaternion();
	}

	Quaternion Quaternion::Euler(const Vector3f& eulerAngles)
	{
		return Quaternion();
	}

	Quaternion Quaternion::LookRotation(const Vector3f & lookDirection)
	{
		return Quaternion();
	}

	Quaternion Quaternion::LookRotation(const Vector3f & lookDirection, const Vector3f& up)
	{
		return Quaternion();
	}

	Quaternion Quaternion::Slerp(const Quaternion& from, const Quaternion& to, const Float32& time)
	{
		return Quaternion();
	}

	Quaternion Quaternion::Identity()
	{
		return Quaternion();
	}

	Quaternion Quaternion::RotationBetween(Vector3f a, Vector3f b)
	{
		return Quaternion();
	}

	Vector3f Quaternion::GetEulerAngles() const
	{
		return Vector3f::Zero();
	}

	Matrix4x4 Quaternion::GetRotationMatrix() const
	{
		return Matrix4x4();
	}

	Vector3f Quaternion::GetDirection() const
	{
		return Vector3f::Zero();
	}

}
}