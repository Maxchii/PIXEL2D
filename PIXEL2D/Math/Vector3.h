#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"
#include <iostream>

namespace PIXL { namespace math {

	inline Float32 Clamp(float value, float min, float max);
	inline Float32 ToRadians(float degrees);

	struct Vector3
	{
		Float32 x, y, z;

		Vector3() = default;
		Vector3(const Float32& x, const Float32& y, const Float32& z) : x(x), y(y), z(z){ }
		void Set(const Float32& x, const Float32& y, const Float32& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		static Float32 Angle(const Vector3& from, const Vector3& to)
		{
			Float32 const angle(acos(Clamp(Dot(from, to), -1.0f, 0.0f)));
			return angle;

			return 0;
		}
		static Vector3 ClampMagnitude(const Vector3& vec, float maxLength)
		{
			Float32 magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			return vec.Normalized() * magnitude;
		}
		static Float32 Distance(const Vector3& a, const Vector3& b)
		{
			return sqrt(
				pow((a.x - b.x), 2)
				+ pow((a.y - b.y), 2)
				+ pow((a.z - b.z), 2));
		}
		static Float32 Dot(const Vector3& a, const Vector3& b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}
		static Vector3 Lerp(const Vector3& from, const Vector3& to, float t)
		{
			Vector3 tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			tmp.z = from.z + (to.z - from.z) * t;
			return tmp;
		}
		void Invert()
		{
			*this * -1;
		}

		inline Vector3 Inverse()
		{
			Vector3 tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector3 Reflect(const Vector3& incident, const Vector3& normal)
		{
			return incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector3 Refract(const Vector3& incident, const Vector3& normal, const Float32& theta)
		{
			//We use a Float32 because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector3(0.0f, 0.0f, 0.0f);
			else
				return theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector3 FaceForward(const Vector3& normal, const Vector3& incident, const Vector3& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}
		static Vector3 RotateX(const Vector3& vec, Float32 angle)
		{
			Vector3 tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#else
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.y = vec.y * c - vec.z * s;
			tmp.z = vec.y * s + vec.z * c;
			return tmp;
		}
		static Vector3 RotateY(const Vector3& vec, Float32 angle)
		{
			Vector3 tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#else
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.x = vec.x * c + vec.z * s;
			tmp.z = -vec.x * s + vec.z * c;
			return tmp;
		}
		static Vector3 RotateZ(const Vector3& vec, Float32 angle)
		{

			Vector3 tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#else
			Float32 const c(cos(ToRadians(angle)));
			Float32 const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.x = vec.x * c - vec.y * s;
			tmp.z = vec.x * s + vec.y * c;
			return tmp;
		}

		inline void Scale(const Vector3& scale)
		{
			*this * scale;
		}
		inline void Scale(const Float32& x, const Float32& y, const Float32& z)
		{
			this->x *= x;
			this->y *= y;
			this->z *= z;
		}
		inline Float32 GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		inline Float32 GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		inline Vector3 Normalized() const
		{
			Vector3 tmp;
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float z2 = pow(z, 2);
			float len = sqrt(x2 + y2 + z2);
			tmp.x /= len;
			tmp.y /= len;
			tmp.z /= len;

			return tmp;
		}
		inline void Normalize()
		{
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float z2 = pow(z, 2);
			float len = sqrt(x2 + y2 + z2);
			x /= len;
			y /= len;
			z /= len;
		}

		static const Vector3 Zero() { return Vector3(0.0f, 0.0f, 0.0f); }
		static const Vector3 One()  { return Vector3(1.0f, 1.0f, 1.0f); }
		static const Vector3 Forward()  { return Vector3(0.0f, 0.0f, 1.0f); }
		static const Vector3 Up()  { return Vector3(0.0f, 1.0f, 0.0f); }
		static const Vector3 Down()  { return Vector3(0.0f, -1.0f, 0.0f); }
		static const Vector3 Right()  { return Vector3(1.0f, 0.0f, 0.0f); }
		static const Vector3 Left()  { return Vector3(-1.0f, 0.0f, 0.0f); }

		friend Vector3 operator+(Vector3 left, const Vector3& right)
		{
			Vector3 tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;
			tmp.z = left.z + right.z;

			return tmp;
		}
		friend Vector3 operator-(Vector3 left, const Vector3& right)
		{
			Vector3 tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;
			tmp.z = left.z - right.z;

			return tmp;
		}
		friend Vector3 operator-(Vector3 left, const Float32& right)
		{
			Vector3 tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;
			tmp.z = left.z - right;

			return tmp;
		}
		friend Vector3 operator*(Vector3 left, const Vector3& right)
		{
			Vector3 tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;
			tmp.z = left.z * right.z;

			return tmp;
		}
		friend Vector3 operator*(Vector3 left, const Float32& right)
		{
			left.x *= right;
			left.y *= right;
			left.z *= right;

			return left;
		}
		friend Vector3 operator*(const Float32& left, Vector3 right)
		{
			right.x *= left;
			right.y *= left;
			right.z *= left;

			return right;
		}
		friend Vector3 operator/(Vector3 left, const Vector3& right)
		{
			Vector3 tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;
			tmp.z = left.z / right.z;

			return tmp;
		}

		inline bool operator==(const Vector3& other)
		{
			return x == other.x&& y == other.y&& z == other.z;
		}
		inline bool operator!=(const Vector3& other)
		{
			return !(*this == other);
		}


		inline Vector3& operator+=(const Vector3& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;

			return *this;
		}
		inline Vector3& operator-=(const Vector3& other)
		{
			x = x - other.x;
			y = y - other.y;
			z = z - other.z;

			return *this;
		}
		inline Vector3& operator*=(const Vector3& other)
		{
			x = x * other.x;
			y = y * other.y;
			z = z * other.z;

			return *this;
		}
		inline Vector3& operator/=(const Vector3& other)
		{
			x = x / other.x;
			y = y / other.y;
			z = z / other.z;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
		{
			return stream << "Vector3 [" << vector.x << "," << vector.y << "," << vector.z << "]";
		}
	};

} }