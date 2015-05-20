#pragma once
#include <iostream>
#include "..//Core/ValueTypes.h"
#include "Math.h"

namespace PIXL { namespace math {

	struct Vector4
	{
		Float32 x, y, z, w;

		Vector4() = default;
		Vector4(const Float32& x, const Float32& y, const Float32& z, const Float32& w) : x(x), y(y), z(z), w(w){ }
		Vector4(const Vector3& vec3)
		{
			x = vec3.x;
			y = vec3.y;
			z = vec3.z;
			w = 0.0f;
		}
		Vector4(const Vector2& vec2)
		{
			x = vec2.x;
			y = vec2.y;
			z = 0.0f;
			w = 0.0f;
		}
		void Set(const Float32& x, const Float32& y, const Float32& z, const Float32& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		static Float32 Angle(const Vector4& from, const Vector4& to)
		{
			//Float32 const angle(acos( clamp(Dot(from, to), -1), 0.0f));
			//return angle;

			return 0;
		}
		static Vector4 ClampMagnitude(const Vector4& vec, float maxLength)
		{
			//Float32 magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			//return vec.Normalized() * magnitude;

			return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		}
		static Float32 Distance(const Vector4& a, const Vector4& b)
		{
			return sqrt(
				  pow((a.x - b.x), 2) 
				+ pow((a.y - b.y), 2)
				+ pow((a.z - b.z), 2)
				+ pow((a.w - b.w), 2));
		}
		static Float32 Dot(const Vector4& a, const Vector4& b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}
		static Vector4 Lerp(const Vector4& from, const Vector4& to, float t)
		{
			Vector4 tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			tmp.z = from.z + (to.z - from.z) * t;
			tmp.w = from.w + (to.w - from.w) * t;
			return tmp;
		}

		inline Vector4 Inverse()
		{
			Vector4 tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector4 Reflect(const Vector4& incident, const Vector4& normal)
		{
			return Vector4(0.0f, 0.0f, 0.0f, 0.0f); //incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector4 Refract(const Vector4& incident, const Vector4& normal, const Float32& theta)
		{
			//We use a Float32 because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			else
				return Vector4(0.0f, 0.0f, 0.0f, 0.0f); //theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector4 FaceForward(const Vector4& normal, const Vector4& incident, const Vector4& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}
		static Vector4 RotateX(const Vector4& vec, Float32 angle)
		{
			//TODO add radians version
			Vector4 tmp;
			Float32 const c(cos(angle));
			Float32 const s(sin(angle));

			tmp.y = vec.y * c - vec.z * s;
			tmp.z = vec.y * s + vec.z * c;
			return tmp;
		}
		static Vector4 RotateY(const Vector4& vec, Float32 angle)
		{
			//TODO add radians version
			Vector4 tmp;
			Float32 const c(cos(angle));
			Float32 const s(sin(angle));

			tmp.x = vec.x * c + vec.z * s;
			tmp.z = -vec.x * s + vec.z * c;
			return tmp;
		}
		static Vector4 RotateZ(const Vector4& vec, Float32 angle)
		{
			//TODO add radians version
			Vector4 tmp;
			Float32 const c(cos(angle));
			Float32 const s(sin(angle));

			tmp.x = vec.x * c - vec.y * s;
			tmp.z = vec.x * s + vec.y * c;
			return tmp;
		}

		inline void Scale(const Vector4& scale)
		{
			*this * scale;
		}
		inline void Scale(const Float32& x, const Float32& y, const Float32& z, const Float32& w)
		{
			this->x *= x;
			this->y *= y;
			this->z *= z;
			this->w *= w;
		}
		inline Float32 GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
		}
		inline Float32 GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
		}
		inline Vector4 Normalized() const
		{
			Vector4 tmp;
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float z2 = pow(z, 2);
			float w2 = pow(w, 2);
			float len = sqrt(x2 + y2 + z2 + w2);
			tmp.x /= len;
			tmp.y /= len;
			tmp.z /= len;
			tmp.w /= len;

			return tmp;
		}
		inline void Normalize()
		{
			float x2 = pow(x, 2);
			float y2 = pow(y, 2);
			float z2 = pow(z, 2);
			float w2 = pow(w, 2);
			float len = sqrt(x2 + y2 + z2 + w2);
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		}

		static const Vector4 Zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
		static const Vector4 One()  { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

		friend Vector4 operator+(Vector4 left, const Vector4& right)
		{
			Vector4 tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;
			tmp.z = left.z + right.z;
			tmp.w = left.w + right.w;

			return tmp;
		}
		friend Vector4 operator-(Vector4 left, const Vector4& right)
		{
			Vector4 tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;
			tmp.z = left.z - right.z;
			tmp.w = left.w - right.w;

			return tmp;
		}
		friend Vector4 operator-(Vector4 left, const Float32& right)
		{
			Vector4 tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;
			tmp.z = left.z - right;
			tmp.w = left.w - right;

			return tmp;
		}
		friend Vector4 operator*(Vector4 left, const Vector4& right)
		{
			Vector4 tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;
			tmp.z = left.z * right.z;
			tmp.w = left.w * right.w;

			return tmp;
		}
		friend Vector4 operator*(Vector4 left, const Float32& right)
		{
			Vector4 tmp;
			tmp.x = left.x * right;
			tmp.y = left.y * right;
			tmp.z = left.z * right;
			tmp.w = left.w * right;

			return tmp;
		}
		friend Vector4 operator/(Vector4 left, const Vector4& right)
		{
			Vector4 tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;
			tmp.z = left.z / right.z;
			tmp.w = left.w / right.w;

			return tmp;
		}

		inline bool operator==(const Vector4& other)
		{
			return x == other.x&& y == other.y&& z == other.z&& w == other.w;
		}
		inline bool operator!=(const Vector4& other)
		{
			return !(*this == other);
		}

		inline Vector4& operator+=(const Vector4& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;
			w = w + other.w;

			return *this;
		}
		inline Vector4& operator-=(const Vector4& other)
		{
			x = x - other.x;
			y = y - other.y;
			z = z - other.z;
			w = w - other.w;

			return *this;
		}
		inline Vector4& operator*=(const Vector4& other)
		{
			x = x * other.x;
			y = y * other.y;
			z = z * other.z;
			w = w * other.w;
		}
		inline Vector4& operator/=(const Vector4& other)
		{
			x = x / other.x;
			y = y / other.y;
			z = z / other.z;
			w = w / other.w;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
		{
			return stream << "Vector4 [" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << "]";
		}
	};
} }