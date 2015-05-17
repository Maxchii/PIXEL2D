#include "Vector2.h"
#include "../Utilities/StringExtensions.h"

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <glm\gtx\vector_angle.hpp>
#include <glm\geometric.hpp>
#include <glm\gtx\compatibility.hpp>

namespace PIXL{ namespace math {

	Vector2::Vector2() : glm::vec2(){ }
	Vector2::Vector2(Float32 x, Float32 y) : glm::vec2(x, y){ }
	Vector2::Vector2(const Vector2& vec) : glm::vec2(vec.x, vec.y){ }
	Vector2::Vector2(const glm::vec2& vec) : glm::vec2(vec){ }

	float Vector2::Angle(const Vector2& from, const Vector2& to)
	{
		glm::vec2 fromRaw = from.Raw();
		glm::vec2 toRaw = to.Raw();
		return glm::angle(fromRaw, toRaw);
	}
	PIXL::math::Vector2 Vector2::ClampMagnitude(const Vector2& vec, float maxLength)
	{
		float magnitude = glm::clamp(vec.GetMagnitude(), -maxLength, maxLength);
		return vec.Normalized()* magnitude;
	}
	float Vector2::Distance(const Vector2& from, const Vector2& to)
	{
		return glm::distance(from.Raw(), to.Raw());
	}
	float Vector2::Dot(const Vector2& from, const Vector2& to)
	{
		return glm::dot(from.Raw(), to.Raw());
	}
	PIXL::math::Vector2 Vector2::Lerp(const Vector2& from, const Vector2& to, float time)
	{
		return Vector2(glm::lerp(from.Raw(), to.Raw(), time));
	}

	PIXL::math::Vector2 Vector2::Reflect(const Vector2& incident, const Vector2& normal)
	{
		return Vector2(glm::reflect(incident.Raw(), normal.Raw()));
	}
	PIXL::math::Vector2 Vector2::Refract(const Vector2& incident, const Vector2& normal, const float& theta)
	{
		return Vector2(glm::refract(incident.Raw(), normal.Raw(), theta));
	}
	PIXL::math::Vector2 Vector2::FaceForward(const Vector2& normal, const Vector2& incident, const Vector2& normalRef)
	{
		return Vector2(glm::faceforward(normal.Raw(), incident.Raw(), normalRef.Raw()));
	}

	PIXL::math::Vector2 Vector2::Rotate(const Vector2& vec, const float& angle)
	{
		return Vector2(glm::rotate(vec.Raw(), angle));
	}

	void Vector2::Scale(const Vector2& scale)
	{
		x = scale.x* x;
		y = scale.y* y;
	}
	void Vector2::Scale(const float& aX, const float& aY)
	{
		x = aX* x;
		y = aY* y;
	}
	float Vector2::GetMagnitude() const
	{
		return glm::sqrt(x* x + y* y);
	}
	float Vector2::GetSqrMagnitude() const
	{
		return x* x + y* y;
	}
	Vector2 Vector2::Normalized() const
	{
		glm::vec2 vec(x, y);
		return Vector2(glm::normalize(vec));
	}
	void Vector2::Normalize()
	{
		glm::vec2 vec(x, y);
		vec = glm::normalize(vec);
		x =vec.x;
		y =vec.y;
	}

	void Vector2::Set(Float32 x, Float32 y)
	{
		this->x = x;
		this->y = y;
	}

	void Vector2::Set(const Vector2& vec)
	{
		this->x =vec.x;
		this->y =vec.y;
	}

	glm::vec2 Vector2::Raw() const
	{
		return glm::vec2(x, y);
	}

	std::string Vector2::ToString()
	{
		return std::string(
			"Vector2 [").append(utilities::F2S(x))
			.append(", ").append(utilities::F2S(y).append("]"));
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		return stream << "Vector2 [" << vector.x << ", " << vector.y << "]";
	}
}
}

#ifdef GLM_FORCE_RADIANS
#undef GLM_FORCE_RADIANS
#endif