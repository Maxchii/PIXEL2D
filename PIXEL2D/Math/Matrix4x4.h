#pragma once
#include "Math.h"
#include <xmmintrin.h>

namespace PIXL { namespace math {

	struct Matrix4x4
	{
		union
		{
			Float32 elements[16];
			Vector4 columns[4];
		};

		Matrix4x4();
		Matrix4x4(float diagonal);

		static Matrix4x4 Identity();

		Matrix4x4& Multiply(const Matrix4x4& other);
		Vector3 Multiply(const Vector3& other) const;
		Vector4 Multiply(const Vector4& other) const;
		

		Matrix4x4& Inverse();
		Matrix4x4& Transpose();

		static Matrix4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4x4 Perspective(float fov, float aspectRatio, float near, float far);

		static Matrix4x4 Translation(const Vector3& translation);
		void Translate(const Vector3& translation);
		
		static Matrix4x4 Rotation(float angle, const Vector3& axis);
		void Rotate(float angle, const Vector3& axis);

		static Matrix4x4 Scaled(const Vector3& scale);
		void Scale(const Vector3& scale);

		friend Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right);
		Matrix4x4& operator*=(const Matrix4x4& other);
		friend Vector3 operator*(const Matrix4x4& left, const Vector3& right);
		friend Vector4 operator*(const Matrix4x4& left, const Vector4& right);
	};

} }