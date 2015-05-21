#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"
#include <iostream>

namespace PIXL { namespace math {

	inline Float32 Clamp(float value, float min, float max);
	inline Float32 ToRadians(float degrees);

	struct Vector2
	{
		Float32 x, y;

		Vector2() = default;
		Vector2(const Float32& x, const Float32& y) : x(x), y(y){ }
		void Set(const Float32& x, const Float32& y)
		{
			this->x = x;
			this->y = y;
		}

		static Float32 Angle(const Vector2& from, const Vector2& to)
		{
			Float32 const angle(acos(Clamp(Dot(from, to), -1.0f, 0.0f)));
			return angle;

			return 0;
		}
		static Vector2 ClampMagnitude(const Vector2& vec, float maxLength)
		{
			Float32 magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			return vec.Normalized() * magnitude;
		}
		static Float32 Distance(const Vector2& a, const Vector2& b)
		{
			return sqrt(
				pow((a.x - b.x), 2)
				+ pow((a.y - b.y), 2));
		}
		static Float32 Dot(const Vector2& a, const Vector2& b)
		{
			return (a.x * b.x) + (a.y * b.y);
		}
		static Vector2 Lerp(const Vector2& from, const Vector2& to, float t)
		{
			Vector2 tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			return tmp;
		}
		void Invert()
		{
			*this * -1;
		}

		inline Vector2 Inverse()
		{
			Vector2 tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector2 Reflect(const Vector2& incident, const Vector2& normal)
		{
			return incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector2 Refract(const Vector2& incident, const Vector2& normal, const Float32& theta)
		{
			//We use a Float32 because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector2(0.0f, 0.0f);
			else
				return theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector2 FaceForward(const Vector2& normal, const Vector2& incident, const Vector2& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}

		inline void Scale(const Vector2& scale)
		{
			*this * scale;
		}
		inline void Scale(const Float32& x, const Float32& y)
		{
			this->x *= x;
			this->y *= y;
		}
		inline Float32 GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}
		inline Float32 GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2));
		}
		inline Vector2 Normalized() const
		{
			Vector2 tmp;
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float len = sqrt(x2 + y2);
			tmp.x /= len;
			tmp.y /= len;

			return tmp;
		}
		inline void Normalize()
		{
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float len = sqrt(x2 + y2);
			x /= len;
			y /= len;
		}

		static const Vector2 Zero() { return Vector2(0.0f, 0.0f); }
		static const Vector2 One()  { return Vector2(1.0f, 1.0f); }
		static const Vector2 Up()  { return Vector2(0.0f, 1.0f); }
		static const Vector2 Down()  { return Vector2(0.0f, -1.0f); }
		static const Vector2 Right()  { return Vector2(1.0f, 0.0f); }
		static const Vector2 Left()  { return Vector2(-1.0f, 0.0f); }

		friend Vector2 operator+(Vector2 left, const Vector2& right)
		{
			Vector2 tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;

			return tmp;
		}
		friend Vector2 operator-(Vector2 left, const Vector2& right)
		{
			Vector2 tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;

			return tmp;
		}
		friend Vector2 operator-(Vector2 left, const Float32& right)
		{
			Vector2 tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;

			return tmp;
		}
		friend Vector2 operator*(Vector2 left, const Vector2& right)
		{
			Vector2 tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;

			return tmp;
		}
		friend Vector2 operator*(Vector2 left, const Float32& right)
		{
			left.x *= right;
			left.y *= right;

			return left;
		}
		friend Vector2 operator*(const Float32& left, Vector2 right)
		{
			right.x *= left;
			right.y *= left;

			return right;
		}
		friend Vector2 operator/(Vector2 left, const Vector2& right)
		{
			Vector2 tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;

			return tmp;
		}

		inline bool operator==(const Vector2& other)
		{
			return x == other.x&& y == other.y;
		}
		inline bool operator!=(const Vector2& other)
		{
			return !(*this == other);
		}


		inline Vector2& operator+=(const Vector2& other)
		{
			x = x + other.x;
			y = y + other.y;

			return *this;
		}
		inline Vector2& operator-=(const Vector2& other)
		{
			x = x - other.x;
			y = y - other.y;

			return *this;
		}
		inline Vector2& operator*=(const Vector2& other)
		{
			x = x * other.x;
			y = y * other.y;

			return *this;
		}
		inline Vector2& operator/=(const Vector2& other)
		{
			x = x / other.x;
			y = y / other.y;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
		{
			return stream << "Vector2 [" << vector.x << "," << vector.y << "]";
		}
	};

} }