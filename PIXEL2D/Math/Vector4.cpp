#include "Vector4.h"
#include "../Utilities/StringExtensions.h"

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm\gtx\vector_angle.hpp>
#include <glm\geometric.hpp>
#include <glm\gtx\compatibility.hpp>

namespace PIXL{ namespace math {

	Vector4::Vector4(Float32 x, Float32 y, Float32 z, Float32 w) : glm::vec4(x, y, z, w){ }
	Vector4::Vector4(const Vector4& aVec) : glm::vec4(aVec.x, aVec.y, aVec.z, aVec.w){ }
	Vector4::Vector4(const glm::vec4& aVec) :glm::vec4(aVec){ }

	PIXL::Float32 Vector4::Angle(const Vector4& from, const Vector4& to)
	{
		return glm::angle(from.Raw(), to.Raw());
	}
	PIXL::math::Vector4 Vector4::ClampMagnitude(const Vector4& vec, float maxLength)
	{
		Float32 magnitude = glm::clamp(vec.GetMagnitude(), -maxLength, maxLength);
		return vec.Normalized() * magnitude;
	}
	PIXL::Float32 Vector4::Distance(const Vector4& from, const Vector4& to)
	{
		return glm::distance(from.Raw(), to.Raw());
	}
	PIXL::Float32 Vector4::Dot(const Vector4& from, const Vector4& to)
	{
		return glm::dot(from.Raw(), to.Raw());
	}

	PIXL::math::Vector4 Vector4::Lerp(const Vector4& from, const Vector4& to, float time)
	{
		return Vector4(glm::lerp(from.Raw(), to.Raw(), time));
	}

	PIXL::math::Vector4 Vector4::Reflect(const Vector4& incident, const Vector4& normal)
	{
		return Vector4(glm::reflect(incident.Raw(), normal.Raw()));
	}
	PIXL::math::Vector4 Vector4::Refract(const Vector4& incident, const Vector4& normal, const Float32& theta)
	{
		return Vector4(glm::refract(incident.Raw(), normal.Raw(), theta));
	}
	PIXL::math::Vector4 Vector4::FaceForward(const Vector4& normal, const Vector4& incident, const Vector4& normalRef)
	{
		return Vector4(glm::faceforward(normal.Raw(), incident.Raw(), normalRef.Raw()));
	}
	PIXL::math::Vector4 Vector4::RotateX(const Vector4& vec, Float32 angle)
	{
		return Vector4(glm::rotateX(vec.Raw(), angle));
	}
	PIXL::math::Vector4 Vector4::RotateY(const Vector4& vec, Float32 angle)
	{
		return Vector4(glm::rotateY(vec.Raw(), angle));
	}
	PIXL::math::Vector4 Vector4::RotateZ(const Vector4& vec, Float32 angle)
	{
		return Vector4(glm::rotateZ(vec.Raw(), angle));
	}

	void Vector4::Scale(const Vector4& scale)
	{
		x = scale.x * x;
		y = scale.y * y;
		z = scale.z * z;
		w = scale.w * w;
	}
	void Vector4::Scale(const Float32& x, const Float32& y, const Float32& z, const Float32& w)
	{
		this->x = x * x;
		this->y = y * y;
		this->z = z * z;
		this->w = w * w;
	}
	Float32 Vector4::GetMagnitude() const
	{
		return glm::sqrt(x * x + y * y + z * z + w * w);
	}
	Float32 Vector4::GetSqrMagnitude() const
	{
		return x * x + y * y + z * z + w * w;
	}
	Vector4 Vector4::Normalized() const
	{
		return Vector4(glm::normalize(Raw()));
	}

	void Vector4::Normalize()
	{
		glm::vec4 vec = glm::normalize(Raw());
		x =vec.x;
		y =vec.y;
		z =vec.z;
		w =vec.w;
	}

	void Vector4::Set(Float32 x, Float32 y, Float32 z, Float32 w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vector4::Set(const Vector4& vec)
	{
		this->x =vec.x;
		this->y =vec.y;
		this->z =vec.z;
		this->w =vec.w;
	}

	//Converts the data into raw 8 bit format. (12 bytes)
	glm::vec4 Vector4::Raw() const
	{
		return glm::vec4(x, y, z, w);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		return stream << "Vector4 [" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "]";
	}

	std::string Vector4::ToString()
	{
		return std::string(
			"Vector4 [").append(utilities::F2S(x)).append(", ")
			.append(utilities::F2S(y).append(", ")
			.append(utilities::F2S(z)).append(", ")
			.append(utilities::F2S(w).append("]")));
	}

} }

#ifdef GLM_FORCE_RADIANS
#undef GLM_FORCE_RADIANS
#endif