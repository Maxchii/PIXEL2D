#pragma once
#include "MathTypes.h"

namespace PIXL { namespace math{

	class Matrix4x4 final: public glm::mat4
	{
	public:
		Matrix4x4();
		Matrix4x4(const glm::mat4x4& matrix);
		~Matrix4x4();

		static Matrix4x4 Transpose(const Matrix4x4& matrix);
		static Matrix4x4 Inverse(const Matrix4x4& matrix);
		static Matrix4x4 Scale(const Matrix4x4& matrix, const Vector3& scale);
		static Matrix4x4 Translate(const Matrix4x4& matrix, const Vector3& translation);
		static Matrix4x4 Rotate(const Matrix4x4& matrix, const Float32& rotation, const Vector3& axis);
		static Matrix4x4 Rotate(const Matrix4x4& matrix, const Vector3& rotation);
		static Matrix4x4 Ortho(const Float32& left, const Float32& right, const Float32& bottom, const Float32& top, const Float32& far, const Float32& near);
		static Matrix4x4 Perspective(const Float32& fov, const Float32& aspectRatio, const Float32& near, const Float32& far);
		static Matrix4x4 LookAt(const Vector3& cameraPosition, const Vector3& direction, const Vector3& upDirection);
		static Matrix4x4 LookAt(const Vector3& cameraPosition, const Vector3& direction);
		static Matrix4x4 Identity();
		static Matrix4x4 Translate(const Vector3& position, const Vector3& rotation, const Vector3& scale);
		static Matrix4x4 Translate(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

		void Transpose();
		void Inverse();
		void Scale(const Vector3& scale);
		void Translate(const Vector3& translation);
		void Rotate(const Float32& rotation, const Float32& angle, const Vector3& axis);
		void Rotate(const Vector3& rotation);
		void SetIdentity();
		Quaternion GetRotation() const;

		glm::mat4 Raw() const;

		friend Vector3 operator*(const Matrix4x4& left, const Vector3& right);

		Matrix4x4 operator*=(const Matrix4x4& matrix);

		Matrix4x4 operator*(const Matrix4x4& matrix);
	};

} }