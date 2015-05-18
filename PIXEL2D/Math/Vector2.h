#pragma once
#include <iostream>

namespace PIXL { namespace math {

	struct Vector2
	{
		float x, y;

		Vector2() = default;
		Vector2(const float& x, const float& y);

		void Set(const float& x, const float& y);

		Vector2& Add(const Vector2& other);
		Vector2& Subtract(const Vector2& other);
		Vector2& Multiply(const Vector2& other);
		Vector2& Divide(const Vector2& other);

		void Normalize();
		Vector2 Normalized();
		float Length();
		void Invert();
		Vector2 Inverted();
		float Distance(const Vector2& other);
		float Magnitude();
		float Dot(const Vector2& a, const Vector2& b);
		

		friend Vector2 operator+(Vector2 left, const Vector2& right);
		friend Vector2 operator-(Vector2 left, const Vector2& right);
		friend Vector2 operator*(Vector2 left, const Vector2& right);
		friend Vector2 operator/(Vector2 left, const Vector2& right);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);

		inline static const Vector2 Zero()		{ return Vector2(0, 0); }
		inline static const Vector2 One()		{ return Vector2(1, 1); }
		inline static const Vector2 Up()		{ return Vector2(0, 1); }
		inline static const Vector2 Right()	{ return Vector2(1, 0); }
		static Vector2 Lerp(const Vector2& from, const Vector2& to, float t);
		

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
	};

} }