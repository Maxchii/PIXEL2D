#pragma once
#include <iostream>

namespace PIXL { namespace math {

	struct Vector3
	{
		float x, y, z;

		Vector3() = default;
		Vector3(const float& x, const float& y, const float& z);

		void Set(const float& x, const float& y, const float& z);

		Vector3& Add(const Vector3& other);
		Vector3& Subtract(const Vector3& other);
		Vector3& Multiply(const Vector3& other);
		Vector3& Divide(const Vector3& other);

		float Length();
		void Normalize();
		Vector3 Normalized();
		void Invert();
		Vector3 Inverted();
		float Distance(const Vector3& other);
		float Magnitude();
		float Dot(const Vector3& a, const Vector3& b);

		friend Vector3 operator+(Vector3 left, const Vector3& right);
		friend Vector3 operator-(Vector3 left, const Vector3& right);
		friend Vector3 operator*(Vector3 left, const Vector3& right);
		friend Vector3 operator/(Vector3 left, const Vector3& right);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);

		inline static const Vector3 Zero()		{ return Vector3(0, 0, 0); }
		inline static const Vector3 One()		{ return Vector3(1, 1, 1); }
		inline static const Vector3 Up()		{ return Vector3(0, 1, 0); }
		inline static const Vector3 Right()		{ return Vector3(1, 0, 0); }
		inline static const Vector3 Forward()   { return Vector3(0, 0, 1); }
		static Vector3 Lerp(const Vector3& from, const Vector3& to, float t);

		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
	};

} }