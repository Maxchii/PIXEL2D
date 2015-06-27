#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"
#include <iostream>

namespace PIXL { namespace math {

	inline Float32 Clamp(float value, float min, float max);
	inline Float32 ToRadians(float degrees);

	template<class T> 
	class Vector4
	{
	public:
		T x, y, z, w;

		Vector4<T>() = default;
		Vector4<T>(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w){ }
		void Set(const T& x, const T& y, const T& z, const T& w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		static T Angle(const Vector4<T>& from, const Vector4<T>& to)
		{
			T const angle(acos(Clamp(Dot(from, to), -1.0f, 0.0f)));
			return angle;

			return 0;
		}
		static Vector4<T> ClampMagnitude(const Vector4<T>& vec, float maxLength)
		{
			T magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			return vec.Normalized() * magnitude;
		}
		static T Distance(const Vector4<T>& a, const Vector4<T>& b)
		{
			return sqrt(
				pow((a.x - b.x), 2)
				+ pow((a.y - b.y), 2)
				+ pow((a.z - b.z), 2)
				+ pow((a.w - b.w), 2));
		}
		static T Dot(const Vector4<T>& a, const Vector4<T>& b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
		}
		static Vector4<T> Lerp(const Vector4<T>& from, const Vector4<T>& to, float t)
		{
			Vector4<T> tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			tmp.z = from.z + (to.z - from.z) * t;
			tmp.w = from.w + (to.w - from.w) * t;
			return tmp;
		}
		void Invert()
		{
			*this * -1;
		}

		inline Vector4<T> Inverse()
		{
			Vector4<T> tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector4<T> Reflect(const Vector4<T>& incident, const Vector4<T>& normal)
		{
			return incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector4<T> Refract(const Vector4<T>& incident, const Vector4<T>& normal, const T& theta)
		{
			//We use a T because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector4<T>(0.0f, 0.0f, 0.0f, 0.0f);
			else
				return theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector4<T> FaceForward(const Vector4<T>& normal, const Vector4<T>& incident, const Vector4<T>& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}
		static Vector4<T> RotateX(const Vector4<T>& vec, T angle)
		{
			//TODO add radians version
			Vector4<T> tmp;
			T const c(cos(angle));
			T const s(sin(angle));

			tmp.y = vec.y * c - vec.z * s;
			tmp.z = vec.y * s + vec.z * c;
			return tmp;
		}
		static Vector4<T> RotateY(const Vector4<T>& vec, T angle)
		{
			//TODO add radians version
			Vector4<T> tmp;
			T const c(cos(angle));
			T const s(sin(angle));

			tmp.x = vec.x * c + vec.z * s;
			tmp.z = -vec.x * s + vec.z * c;
			return tmp;
		}
		static Vector4<T> RotateZ(const Vector4<T>& vec, T angle)
		{
			//TODO add radians version
			Vector4<T> tmp;
			T const c(cos(angle));
			T const s(sin(angle));

			tmp.x = vec.x * c - vec.y * s;
			tmp.z = vec.x * s + vec.y * c;
			return tmp;
		}

		inline void Scale(const Vector4<T>& scale)
		{
			*this * scale;
		}
		inline void Scale(const T& x, const T& y, const T& z, const T& w)
		{
			this->x *= x;
			this->y *= y;
			this->z *= z;
			this->w *= w;
		}
		inline T GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
		}
		inline T GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
		}
		inline Vector4<T> Normalized() const
		{
			Vector4<T> tmp;
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

		static const Vector4<T> Zero() { return Vector4<T>(0.0f, 0.0f, 0.0f, 0.0f); }
		static const Vector4<T> One()  { return Vector4<T>(1.0f, 1.0f, 1.0f, 1.0f); }

		friend Vector4<T> operator+(Vector4<T> left, const Vector4<T>& right)
		{
			Vector4<T> tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;
			tmp.z = left.z + right.z;
			tmp.w = left.w + right.w;

			return tmp;
		}
		friend Vector4<T> operator-(Vector4<T> left, const Vector4<T>& right)
		{
			Vector4<T> tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;
			tmp.z = left.z - right.z;
			tmp.w = left.w - right.w;

			return tmp;
		}
		friend Vector4<T> operator-(Vector4<T> left, const T& right)
		{
			Vector4<T> tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;
			tmp.z = left.z - right;
			tmp.w = left.w - right;

			return tmp;
		}
		friend Vector4<T> operator*(Vector4<T> left, const Vector4<T>& right)
		{
			Vector4<T> tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;
			tmp.z = left.z * right.z;
			tmp.w = left.w * right.w;

			return tmp;
		}
		friend Vector4<T> operator*(Vector4<T> left, const T& right)
		{
			left.x *= right;
			left.y *= right;
			left.z *= right;
			left.w *= right;

			return left;
		}
		friend Vector4<T> operator*(const T& left, Vector4<T> right)
		{
			right.x *= left;
			right.y *= left;
			right.z *= left;
			right.w *= left;

			return right;
		}
		friend Vector4<T> operator/(Vector4<T> left, const Vector4<T>& right)
		{
			Vector4<T> tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;
			tmp.z = left.z / right.z;
			tmp.w = left.w / right.w;

			return tmp;
		}

		inline bool operator==(const Vector4<T>& other)
		{
			return x == other.x&& y == other.y&& z == other.z&& w == other.w;
		}
		inline bool operator!=(const Vector4<T>& other)
		{
			return !(*this == other);
		}


		inline Vector4<T>& operator+=(const Vector4<T>& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;
			w = w + other.w;

			return *this;
		}
		inline Vector4<T>& operator-=(const Vector4<T>& other)
		{
			x = x - other.x;
			y = y - other.y;
			z = z - other.z;
			w = w - other.w;

			return *this;
		}
		inline Vector4<T>& operator*=(const Vector4<T>& other)
		{
			x = x * other.x;
			y = y * other.y;
			z = z * other.z;
			w = w * other.w;

			return *this;
		}
		inline Vector4<T>& operator/=(const Vector4<T>& other)
		{
			x = x / other.x;
			y = y / other.y;
			z = z / other.z;
			w = w / other.w;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector4<T>& vector)
		{
			return stream << "Vector4<T> [" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << "]";
		}
	};

	using Vector4f = Vector4 < float > ;
	using Vector4i = Vector4 < int > ;
	using Vector4d = Vector4 < double >;
} }