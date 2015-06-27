#pragma once
#include "Math.h"
#include <xmmintrin.h>

namespace PIXL { namespace math {

	struct Matrix4x4
	{
		Float32 elements[16];

		Matrix4x4();
		Matrix4x4(float diagonal);

		static Matrix4x4 Identity();

		Matrix4x4& Multiply(const Matrix4x4& other);
		Vector3f Multiply(const Vector3f& other) const;
		Vector4f Multiply(const Vector4f& other) const;
		

		Matrix4x4& Inverse();
		Matrix4x4& Transpose();

		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4x4 Perspective(float fov, float aspectRatio, float near, float far);

		static Matrix4x4 Translation(const Vector3f& translation);
		void Translate(const Vector3f& translation);
		
		static Matrix4x4 Rotation(float angle, const Vector3f& axis);
		void Rotate(float angle, const Vector3f& axis);

		static Matrix4x4 Scaled(const Vector3f& scale);
		void Scale(const Vector3f& scale);

		friend Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right);
		Matrix4x4& operator*=(const Matrix4x4& other);
		friend Vector3f operator*(const Matrix4x4& left, const Vector3f& right);
		friend Vector4f operator*(const Matrix4x4& left, const Vector4f& right);
	};

} }