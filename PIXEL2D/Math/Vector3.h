#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"
#include <iostream>

namespace PIXL { namespace math {

	inline Float32 Clamp(float value, float min, float max);
	inline Float32 ToRadians(float degrees);

	template<class T>
	class Vector3
	{
	public:
		T x, y, z;

		Vector3<T>() = default;
		Vector3<T>(const T& x, const T& y, const T& z) : x(x), y(y), z(z){ }
		void Set(const T& x, const T& y, const T& z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		static T Angle(const Vector3<T>& from, const Vector3<T>& to)
		{
			T const angle(acos(Clamp(Dot(from, to), -1.0f, 0.0f)));
			return angle;

			return 0;
		}
		static Vector3<T> ClampMagnitude(const Vector3<T>& vec, float maxLength)
		{
			T magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			return vec.Normalized() * magnitude;
		}
		static T Distance(const Vector3<T>& a, const Vector3<T>& b)
		{
			return sqrt(
				pow((a.x - b.x), 2)
				+ pow((a.y - b.y), 2)
				+ pow((a.z - b.z), 2));
		}
		static T Dot(const Vector3<T>& a, const Vector3<T>& b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}
		static Vector3<T> Lerp(const Vector3<T>& from, const Vector3<T>& to, float t)
		{
			Vector3<T> tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			tmp.z = from.z + (to.z - from.z) * t;
			return tmp;
		}
		void Invert()
		{
			*this * -1;
		}

		inline Vector3<T> Inverse()
		{
			Vector3<T> tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector3<T> Reflect(const Vector3<T>& incident, const Vector3<T>& normal)
		{
			return incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector3<T> Refract(const Vector3<T>& incident, const Vector3<T>& normal, const T& theta)
		{
			//We use a T because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector3<T>(0.0f, 0.0f, 0.0f);
			else
				return theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector3<T> FaceForward(const Vector3<T>& normal, const Vector3<T>& incident, const Vector3<T>& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}
		static Vector3<T> RotateX(const Vector3<T>& vec, T angle)
		{
			Vector3<T> tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#else
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.y = vec.y * c - vec.z * s;
			tmp.z = vec.y * s + vec.z * c;
			return tmp;
		}
		static Vector3<T> RotateY(const Vector3<T>& vec, T angle)
		{
			Vector3<T> tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#else
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.x = vec.x * c + vec.z * s;
			tmp.z = -vec.x * s + vec.z * c;
			return tmp;
		}
		static Vector3<T> RotateZ(const Vector3<T>& vec, T angle)
		{

			Vector3<T> tmp;
#ifdef PIXL_MATH_FORCE_RADIANS
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#else
			T const c(cos(ToRadians(angle)));
			T const s(sin(ToRadians(angle)));
#endif // PIXL_MATH_FORCE_RADIANS

			tmp.x = vec.x * c - vec.y * s;
			tmp.z = vec.x * s + vec.y * c;
			return tmp;
		}

		inline void Scale(const Vector3<T>& scale)
		{
			*this * scale;
		}
		inline void Scale(const T& x, const T& y, const T& z)
		{
			this->x *= x;
			this->y *= y;
			this->z *= z;
		}
		inline T GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		inline T GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2) + pow(z, 2));
		}
		inline Vector3<T> Normalized() const
		{
			Vector3<T> tmp;
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

		static const Vector3<T> Zero() { return Vector3<T>(0.0f, 0.0f, 0.0f); }
		static const Vector3<T> One()  { return Vector3<T>(1.0f, 1.0f, 1.0f); }
		static const Vector3<T> Forward()  { return Vector3<T>(0.0f, 0.0f, 1.0f); }
		static const Vector3<T> Up()  { return Vector3<T>(0.0f, 1.0f, 0.0f); }
		static const Vector3<T> Down()  { return Vector3<T>(0.0f, -1.0f, 0.0f); }
		static const Vector3<T> Right()  { return Vector3<T>(1.0f, 0.0f, 0.0f); }
		static const Vector3<T> Left()  { return Vector3<T>(-1.0f, 0.0f, 0.0f); }

		friend Vector3<T> operator+(Vector3<T> left, const Vector3<T>& right)
		{
			Vector3<T> tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;
			tmp.z = left.z + right.z;

			return tmp;
		}
		friend Vector3<T> operator-(Vector3<T> left, const Vector3<T>& right)
		{
			Vector3<T> tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;
			tmp.z = left.z - right.z;

			return tmp;
		}
		friend Vector3<T> operator-(Vector3<T> left, const T& right)
		{
			Vector3<T> tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;
			tmp.z = left.z - right;

			return tmp;
		}
		friend Vector3<T> operator*(Vector3<T> left, const Vector3<T>& right)
		{
			Vector3<T> tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;
			tmp.z = left.z * right.z;

			return tmp;
		}
		friend Vector3<T> operator*(Vector3<T> left, const T& right)
		{
			left.x *= right;
			left.y *= right;
			left.z *= right;

			return left;
		}
		friend Vector3<T> operator*(const T& left, Vector3<T> right)
		{
			right.x *= left;
			right.y *= left;
			right.z *= left;

			return right;
		}
		friend Vector3<T> operator/(Vector3<T> left, const Vector3<T>& right)
		{
			Vector3<T> tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;
			tmp.z = left.z / right.z;

			return tmp;
		}

		inline bool operator==(const Vector3<T>& other)
		{
			return x == other.x&& y == other.y&& z == other.z;
		}
		inline bool operator!=(const Vector3<T>& other)
		{
			return !(*this == other);
		}


		inline Vector3<T>& operator+=(const Vector3<T>& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;

			return *this;
		}
		inline Vector3<T>& operator-=(const Vector3<T>& other)
		{
			x = x - other.x;
			y = y - other.y;
			z = z - other.z;

			return *this;
		}
		inline Vector3<T>& operator*=(const Vector3<T>& other)
		{
			x = x * other.x;
			y = y * other.y;
			z = z * other.z;

			return *this;
		}
		inline Vector3<T>& operator/=(const Vector3<T>& other)
		{
			x = x / other.x;
			y = y / other.y;
			z = z / other.z;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector3<T>& vector)
		{
			return stream << "Vector3<T> [" << vector.x << "," << vector.y << "," << vector.z << "]";
		}
	};

	using Vector3f = Vector3< float > ;
	using Vector3i = Vector3< int > ;
	using Vector3d = Vector3< double > ;
} }