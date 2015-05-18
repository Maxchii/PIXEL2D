#pragma once
#include <iostream>

namespace PIXL { namespace math {

	struct Vector4
	{
		float x, y, z, w;

		Vector4() = default;
		Vector4(const float& x, const float& y, const float& z, const float& w);

		void Set(const float& x, const float& y, const float& z, const float& w);

		Vector4& Add(const Vector4& other);
		Vector4& Subtract(const Vector4& other);
		Vector4& Multiply(const Vector4& other);
		Vector4& Divide(const Vector4& other);

		float Length();
		void Normalize();
		Vector4 Normalized();
		void Invert();
		Vector4 Inverted();
		float Distance(const Vector4& other);
		float Magnitude();
		float Dot(const Vector4& a, const Vector4& b);

		friend Vector4 operator+(Vector4 left, const Vector4& right);
		friend Vector4 operator-(Vector4 left, const Vector4& right);
		friend Vector4 operator*(Vector4 left, const Vector4& right);
		friend Vector4 operator/(Vector4 left, const Vector4& right);

		bool operator==(const Vector4& other);
		bool operator!=(const Vector4& other);

		Vector4& operator+=(const Vector4& other);
		Vector4& operator-=(const Vector4& other);
		Vector4& operator*=(const Vector4& other);
		Vector4& operator/=(const Vector4& other);

		inline static const Vector4 Zero() { return Vector4(0, 0, 0, 0); }
		inline static const Vector4 One()  { return Vector4(1, 1, 1, 1); }
		static Vector4 Lerp(const Vector4& from, const Vector4& to, float t);

		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
	};

} }