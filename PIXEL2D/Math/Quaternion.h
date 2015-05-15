#pragma once
#include "MathTypes.h"
#include <glm\gtc\quaternion.hpp>

namespace PIXL {namespace math {

	class Quaternion final: public glm::quat
	{
	public:
		Quaternion();
		Quaternion(glm::quat& quaternion);
		Quaternion(Float32 w, Float32 x, Float32 y, Float32 z);
		~Quaternion(){}

		static float Angle(const Quaternion& a, const Quaternion& b);
		static float Dot(const Quaternion& a, const Quaternion& b);
		static Quaternion Inverse(const Quaternion& rotation);
		static Quaternion Euler(const Vector3& eulerAngles);
		static Quaternion LookRotation(const Vector3& lookDirection);
		static Quaternion LookRotation(const Vector3& lookDirection, const Vector3& desiredUp);
		static Quaternion Slerp(const Quaternion& from, const Quaternion& to, const Float32& time);
		static Quaternion Identity();

		static Quaternion RotationBetween(Vector3 start, Vector3 end);


		Vector3 GetEulerAngles() const;
		Matrix4x4 GetRotationMatrix() const;
		Vector3 GetDirection() const;

		glm::quat Raw() const;
	};

} }
