#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"

namespace PIXL { namespace math{

	class Quaternion
	{
		Float32 x, y, z, w;
		Quaternion();
		Quaternion(Float32 w, Float32 x, Float32 y, Float32 z);
		void Set(const Float32& x, const Float32& y, const Float32& z, const Float32& w);
		~Quaternion(){};

		static float Angle(const Quaternion& a, const Quaternion& b);
		static float Dot(const Quaternion& a, const Quaternion& b);
		static Quaternion Inverse(const Quaternion& rotation);
		static Quaternion Euler(const Vector3f& eulerAngles);
		static Quaternion LookRotation(const Vector3f & lookDirection);
		static Quaternion LookRotation(const Vector3f & lookDirection, const Vector3f& up);
		static Quaternion Slerp(const Quaternion& from, const Quaternion& to, const Float32& time);
		static Quaternion Identity();
		static Quaternion RotationBetween(Vector3f a, Vector3f b);

		Vector3f GetEulerAngles() const;
		Matrix4x4 GetRotationMatrix() const;
		Vector3f GetDirection() const;

	};

} }