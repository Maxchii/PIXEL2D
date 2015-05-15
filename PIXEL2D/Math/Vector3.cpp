#include "Vector3.h"
#include "Vector4.h"
#include "../Utilities/StringExtensions.h"

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm\gtx\vector_angle.hpp>
#include <glm\geometric.hpp>
#include <glm\gtx\compatibility.hpp>

namespace PIXL { namespace math {

	Vector3::Vector3(Float32 x, Float32 y, Float32 z) : glm::vec3()
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3::Vector3(const Vector3& vec) : glm::vec3()
	{
		x =vec.x;
		y =vec.y;
		z =vec.z;
	}
	Vector3::Vector3(const glm::vec3& vec) : glm::vec3()
	{
		x =vec.x;
		y =vec.y;
		z =vec.z;
	}
	Vector3::Vector3(const Vector4& vec) : glm::vec3()
	{
		x =vec.x;
		y =vec.y;
		z =vec.z;
	}
	float Vector3::Angle(const Vector3& from, const Vector3& to)
	{
		return glm::angle(from.Raw(), to.Raw());
	}
	PIXL::math::Vector3 Vector3::ClampMagnitude(const Vector3& vec, float maxLength)
	{
		float magnitude = glm::clamp(vec.GetMagnitude(), -maxLength, maxLength);
		Vector3 normalizedVector =vec.Normalized();
		return normalizedVector * magnitude;
	}
	float Vector3::Distance(const Vector3& from, const Vector3& to)
	{
		return glm::distance(from.Raw(), to.Raw());
	}
	float Vector3::Dot(const Vector3& from, const Vector3& to)
	{
		return glm::dot(from.Raw(), to.Raw());
	}

	PIXL::math::Vector3 Vector3::Cross(const Vector3& x, const Vector3& y)
	{
		return Vector3(glm::cross(x.Raw(), y.Raw()));
	}
	PIXL::math::Vector3 Vector3::Lerp(const Vector3& from, const Vector3& to, float time)
	{
		return Vector3(glm::lerp(from.Raw(), to.Raw(), time));
	}

	PIXL::math::Vector3 Vector3::Reflect(const Vector3& incident, const Vector3& normal)
	{
		return Vector3(glm::reflect(incident.Raw(), normal.Raw()));
	}
	PIXL::math::Vector3 Vector3::Refract(const Vector3& incident, const Vector3& normal, const float& theta)
	{
		return Vector3(glm::refract(incident.Raw(), normal.Raw(), theta));
	}
	PIXL::math::Vector3 Vector3::FaceForward(const Vector3& normal, const Vector3& incident, const Vector3& normalRef)
	{
		return Vector3(glm::faceforward(normal.Raw(), incident.Raw(), normalRef.Raw()));
	}
	PIXL::math::Vector3 Vector3::RotateX(const Vector3& vec, float angle)
	{
		return Vector3(glm::rotateX(vec.Raw(), angle));
	}
	PIXL::math::Vector3 Vector3::RotateY(const Vector3& vec, float angle)
	{
		return Vector3(glm::rotateY(vec.Raw(), angle));
	}
	PIXL::math::Vector3 Vector3::RotateZ(const Vector3& vec, float angle)
	{
		return Vector3(glm::rotateZ(vec.Raw(), angle));
	}

	void Vector3::Scale(const Vector3& scale)
	{
		x = scale.x * x;
		y = scale.y * y;
		z = scale.z * z;
	}
	void Vector3::Scale(const float& x, const float& y, const float& z)
	{
		this->x = x * x;
		this->y = y * y;
		this->z = z * z;
	}
	float Vector3::GetMagnitude() const
	{
		return glm::sqrt(x*x + y*y + z*z);
	}
	float Vector3::GetSqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}
	Vector3 Vector3::Normalized() const
	{
		return Vector3(glm::normalize(Raw()));
	}
	void Vector3::Normalize()
	{
		glm::vec3 vec = glm::normalize(Raw());
		x =vec.x;
		y =vec.y;
		z =vec.z;
	}

	void Vector3::Set(Float32 x, Float32 y, Float32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3::Set(const Vector3& vec)
	{
		this->x =vec.x;
		this->y =vec.y;
		this->z =vec.z;
	}

	//Converts the data into raw 8 bit format. (12 bytes)
	glm::vec3 Vector3::Raw() const
	{
		return glm::vec3(x, y, z);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		return stream << "Vector3 [" << vector.x << ", " << vector.y << ", " << vector.z << "]";
	}

	std::string Vector3::ToString()
	{
		return std::string(
			"Vector3 [").append(utilities::F2S(x)).append(", ")
			.append(utilities::F2S(y).append(", ")
			.append(utilities::F2S(z)).append("]"));
	}

} }

#ifdef GLM_FORCE_RADIANS
#undef GLM_FORCE_RADIANS
#endif