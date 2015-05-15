#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include <glm\gtx\vector_angle.hpp>

namespace PIXL { namespace math {

	Quaternion::Quaternion() : glm::quat() { }
	Quaternion::Quaternion(glm::quat& quaternion) :  glm::quat(quaternion){ }
	Quaternion::Quaternion(Float32 w, Float32 x, Float32 y, Float32 z) :  glm::quat()
	{
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Quaternion::Angle(const Quaternion& a, const Quaternion& b)
	{
		//TODO: Implement to return an angle between two rotations
		return 0.0f;
	}
	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return glm::dot(a.Raw(), b.Raw());
	}
	Quaternion Quaternion::Inverse(const Quaternion& rotation)
	{
		return Quaternion(glm::inverse(rotation.Raw()));
	}
	Quaternion Quaternion::Euler(const Vector3& eulerAngles)
	{
		return Quaternion(glm::quat(
			glm::vec3(
			glm::radians(eulerAngles.x),
			glm::radians(eulerAngles.y),
			glm::radians(eulerAngles.z))
			));
	}
	Quaternion Quaternion::LookRotation(const Vector3& lookDirection)
	{
		glm::quat quat1 = RotationBetween(Vector3::Forward(), lookDirection).Raw();

		glm::vec3 desiredUp = Vector3::Up().Raw();
		glm::vec3 right = glm::cross(lookDirection, desiredUp);
		desiredUp = glm::cross(right, lookDirection);

		glm::vec3 newUp = quat1 * Vector3::Up().Raw();
		glm::quat quat2 = RotationBetween(newUp, desiredUp);
		return quat2 * quat1;
	}

	Quaternion Quaternion::LookRotation(const Vector3& lookDirection, const Vector3& desiredUp)
	{
		glm::quat quat1 = RotationBetween(Vector3::Forward(), lookDirection).Raw();

		glm::vec3 dUp = desiredUp.Raw();
		glm::vec3 right = glm::cross(lookDirection, dUp);
		dUp = glm::cross(right, lookDirection);

		glm::vec3 newUp = quat1 * Vector3::Up().Raw();
		glm::quat quat2 = RotationBetween(newUp, dUp);
		return quat2 * quat1;
	}
	Quaternion Quaternion::Slerp(const Quaternion& from, const Quaternion& to, const Float32& time)
	{
		return glm::slerp(from.Raw(), to.Raw(), time);
	}

	Quaternion Quaternion::Identity()
	{
		return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	}

	Quaternion Quaternion::RotationBetween(Vector3 start, Vector3 end)
	{
		glm::vec3 s = glm::normalize(start.Raw());
		glm::vec3 e = glm::normalize(end.Raw());

		float cosTheta = glm::dot(s, e);
		glm::vec3 rotationAxis;

		if (cosTheta < -1 + 0.001f)
		{
			rotationAxis = glm::cross(Vector3::Forward(), s);
			if (glm::length2(rotationAxis) < 0.01f)
			{
				rotationAxis = glm::cross(Vector3::Right(), s);
			}
			rotationAxis = glm::normalize(rotationAxis);
			return glm::angleAxis(180.0f, rotationAxis);
		}
		rotationAxis = glm::cross(s, e);

		float sq = glm::sqrt((1 + cosTheta) * 2.0f);
		float invs = 1 / sq;

		return glm::quat(sq * 0.5f, rotationAxis.x * invs, rotationAxis.y * invs, rotationAxis.z * invs);
	}

	Vector3 Quaternion::GetEulerAngles() const
	{
		return Vector3(glm::eulerAngles(Raw()));
	}

	Matrix4x4 Quaternion::GetRotationMatrix() const
	{
		return Matrix4x4(glm::toMat4(Raw()));
	}
	Vector3 Quaternion::GetDirection() const
	{
		return (*this) * Vector3::Forward();
	}
	glm::quat Quaternion::Raw() const
	{
		return glm::quat(w, x, y, z);
	}

} }
