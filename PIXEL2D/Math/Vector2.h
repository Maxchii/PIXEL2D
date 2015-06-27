#pragma once
#include "..//Core/ValueTypes.h"
#include "Math.h"
#include <iostream>

namespace PIXL { namespace math {

	inline Float32 Clamp(float value, float min, float max);
	inline Float32 ToRadians(float degrees);

	template<class T>
	class Vector2
	{
	public:
		T x, y;

		Vector2<T>() = default;
		Vector2<T>(const T& x, const T& y) : x(x), y(y){ }
		void Set(const T& x, const T& y)
		{
			this->x = x;
			this->y = y;
		}

		static T Angle(const Vector2<T>& from, const Vector2<T>& to)
		{
			T const angle(acos(Clamp(Dot(from, to), -1.0f, 0.0f)));
			return angle;

			return 0;
		}
		static Vector2<T> ClampMagnitude(const Vector2<T>& vec, float maxLength)
		{
			T magnitude = Clamp(vec.GetMagnitude(), -maxLength, maxLength);
			return vec.Normalized() * magnitude;
		}
		static T Distance(const Vector2<T>& a, const Vector2<T>& b)
		{
			return sqrt(
				pow((a.x - b.x), 2)
				+ pow((a.y - b.y), 2));
		}
		static T Dot(const Vector2<T>& a, const Vector2<T>& b)
		{
			return (a.x * b.x) + (a.y * b.y);
		}
		static Vector2<T> Lerp(const Vector2<T>& from, const Vector2<T>& to, float t)
		{
			Vector2<T> tmp;
			tmp.x = from.x + (to.x - from.x) * t;
			tmp.y = from.y + (to.y - from.y) * t;
			return tmp;
		}
		void Invert()
		{
			*this * -1;
		}

		inline Vector2<T> Inverse()
		{
			Vector2<T> tmp;
			tmp = *this * -1;

			return tmp;
		}
		static Vector2<T> Reflect(const Vector2<T>& incident, const Vector2<T>& normal)
		{
			return incident - 2.f * Dot(incident, normal) * normal;
		}
		static Vector2<T> Refract(const Vector2<T>& incident, const Vector2<T>& normal, const T& theta)
		{
			//We use a T because a Refract only works with float values

			float N_dot_I = Dot(normal, incident);
			float k = 1.f - theta * theta * (1.f - N_dot_I * N_dot_I);
			if (k < 0.f)
				return Vector2<T>(0.0f, 0.0f);
			else
				return theta * incident - (theta * N_dot_I + sqrtf(k)) * normal;
		}
		static Vector2<T> FaceForward(const Vector2<T>& normal, const Vector2<T>& incident, const Vector2<T>& normalRef)
		{
			return Dot(normalRef, incident) < 0 ? normal : normal * -1;
		}

		inline void Scale(const Vector2<T>& scale)
		{
			*this * scale;
		}
		inline void Scale(const T& x, const T& y)
		{
			this->x *= x;
			this->y *= y;
		}
		inline T GetMagnitude() const
		{
			return sqrt(pow(x, 2) + pow(y, 2));
		}
		inline T GetSqrMagnitude() const
		{
			return (pow(x, 2) + pow(y, 2));
		}
		inline Vector2<T> Normalized() const
		{
			Vector2<T> tmp;
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

		static const Vector2<T> Zero() { return Vector2<T>(0.0f, 0.0f); }
		static const Vector2<T> One()  { return Vector2<T>(1.0f, 1.0f); }
		static const Vector2<T> Up()  { return Vector2<T>(0.0f, 1.0f); }
		static const Vector2<T> Down()  { return Vector2<T>(0.0f, -1.0f); }
		static const Vector2<T> Right()  { return Vector2<T>(1.0f, 0.0f); }
		static const Vector2<T> Left()  { return Vector2<T>(-1.0f, 0.0f); }

		friend Vector2<T> operator+(Vector2<T> left, const Vector2<T>& right)
		{
			Vector2<T> tmp;
			tmp.x = left.x + right.x;
			tmp.y = left.y + right.y;

			return tmp;
		}
		friend Vector2<T> operator-(Vector2<T> left, const Vector2<T>& right)
		{
			Vector2<T> tmp;
			tmp.x = left.x - right.x;
			tmp.y = left.y - right.y;

			return tmp;
		}
		friend Vector2<T> operator-(Vector2<T> left, const T& right)
		{
			Vector2<T> tmp;
			tmp.x = left.x - right;
			tmp.y = left.y - right;

			return tmp;
		}
		friend Vector2<T> operator*(Vector2<T> left, const Vector2<T>& right)
		{
			Vector2<T> tmp;
			tmp.x = left.x * right.x;
			tmp.y = left.y * right.y;

			return tmp;
		}
		friend Vector2<T> operator*(Vector2<T> left, const T& right)
		{
			left.x *= right;
			left.y *= right;

			return left;
		}
		friend Vector2<T> operator*(const T& left, Vector2<T> right)
		{
			right.x *= left;
			right.y *= left;

			return right;
		}
		friend Vector2<T> operator/(Vector2<T> left, const Vector2<T>& right)
		{
			Vector2<T> tmp;
			tmp.x = left.x / right.x;
			tmp.y = left.y / right.y;

			return tmp;
		}

		inline bool operator==(const Vector2<T>& other)
		{
			return x == other.x&& y == other.y;
		}
		inline bool operator!=(const Vector2<T>& other)
		{
			return !(*this == other);
		}


		inline Vector2<T>& operator+=(const Vector2<T>& other)
		{
			x = x + other.x;
			y = y + other.y;

			return *this;
		}
		inline Vector2<T>& operator-=(const Vector2<T>& other)
		{
			x = x - other.x;
			y = y - other.y;

			return *this;
		}
		inline Vector2<T>& operator*=(const Vector2<T>& other)
		{
			x = x * other.x;
			y = y * other.y;

			return *this;
		}
		inline Vector2<T>& operator/=(const Vector2<T>& other)
		{
			x = x / other.x;
			y = y / other.y;

			return *this;
		}

		inline friend std::ostream& operator<<(std::ostream& stream, const Vector2<T>& vector)
		{
			return stream << "Vector2<T> [" << vector.x << "," << vector.y << "]";
		}
	};

	using Vector2i = Vector2 < int > ;
	using Vector2f = Vector2 < float > ;
	using Vector2d = Vector2 < double > ;
} }