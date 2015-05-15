#include "Matrix4x4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>

namespace PIXL { namespace math {

	Matrix4x4::Matrix4x4() : glm::mat4x4(){ }
	Matrix4x4::Matrix4x4(const glm::mat4x4& matrix) : glm::mat4x4(matrix){ }
	Matrix4x4::~Matrix4x4(){ }

	Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& matrix)
	{
		return Matrix4x4(glm::transpose(matrix.Raw()));
	}
	Matrix4x4 Matrix4x4::Inverse(const Matrix4x4& matrix)
	{
		return Matrix4x4(glm::inverse(matrix.Raw()));
	}
	Matrix4x4 Matrix4x4::Scale(const Matrix4x4& matrix, const Vector3& scale)
	{
		return Matrix4x4(glm::scale(matrix.Raw(), scale.Raw()));
	}
	Matrix4x4 Matrix4x4::Translate(const Matrix4x4& matrix, const Vector3& translation)
	{
		Vector4 position = matrix[3];
		position.x += translation.x;
		position.y += translation.y;
		position.z += translation.z;
		Matrix4x4 mat = matrix;
		mat[3] = position;
		return mat;
	}
	Matrix4x4 Matrix4x4::Rotate(const Matrix4x4& matrix, const Float32& rotation, const Vector3& axis)
	{
		return Matrix4x4(glm::rotate(matrix.Raw(), rotation, axis.Raw()));
	}
	Matrix4x4 Matrix4x4::Rotate(const Matrix4x4& matrix, const Vector3& rotation)
	{
		//Rotate ZXY
		glm::mat4x4 mat = matrix.Raw();
		mat = glm::rotate(mat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::rotate(mat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

		return Matrix4x4(mat);
	}
	Matrix4x4 Matrix4x4::Ortho(const Float32& left, const Float32& right, const Float32& top, const Float32& bottom, const Float32& far, const Float32& near)
	{
		return Matrix4x4(glm::ortho(left, right, bottom, top, near, far));
	}
	Matrix4x4 Matrix4x4::Perspective(const Float32& fov, const Float32& aspectRatio, const Float32& near, const Float32& far)
	{
		return Matrix4x4(glm::perspective(fov, aspectRatio, near, far));
	}
	Matrix4x4 Matrix4x4::LookAt(const Vector3& cameraPosition, const Vector3& direction, const Vector3& upDirection)
	{
		//glm::mat4 mat = glm::lookAt(cameraPosition, aTargetPosition, upDirection);
		//Matrix4x4 result = mat;


		Vector3 f = direction.Normalized();
		Vector3 s = Vector3::Cross(f, upDirection).Normalized();
		Vector3 u = Vector3::Cross(s, f);

		Matrix4x4 result = Matrix4x4::Identity();
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -Vector3::Dot(s, cameraPosition);
		result[3][1] = -Vector3::Dot(u, cameraPosition);
		result[3][2] = Vector3::Dot(f, cameraPosition);
		return result;

		return result;
	}

	Matrix4x4 Matrix4x4::LookAt(const Vector3& cameraPosition, const Vector3& direction)
	{
		Vector3 f = direction.Normalized();
		Vector3 s = Vector3::Cross(f, Vector3::Up()).Normalized();
		Vector3 u = Vector3::Cross(s, f);

		Matrix4x4 result = Matrix4x4::Identity();
		result[0][0] = s.x;
		result[1][0] = s.y;
		result[2][0] = s.z;
		result[0][1] = u.x;
		result[1][1] = u.y;
		result[2][1] = u.z;
		result[0][2] = -f.x;
		result[1][2] = -f.y;
		result[2][2] = -f.z;
		result[3][0] = -Vector3::Dot(s, cameraPosition);
		result[3][1] = -Vector3::Dot(u, cameraPosition);
		result[3][2] = Vector3::Dot(f, cameraPosition);
		return result;
	}


	Matrix4x4 Matrix4x4::Identity()
	{
		Matrix4x4 mat;
		memset(&mat, 0, sizeof(Matrix4x4));
		mat[0][0] = 1.0f;
		mat[1][1] = 1.0f;
		mat[2][2] = 1.0f;
		mat[3][3] = 1.0f;
		return mat;
	}

	Matrix4x4 Matrix4x4::Translate(const Vector3& position, const Vector3& rotation, const Vector3& scale)
	{
		Matrix4x4 mat = Matrix4x4::Identity();
		mat.Scale(scale);
		mat.Rotate(rotation);
		mat.Translate(position);
		return mat;
	}

	Matrix4x4 Matrix4x4::Translate(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	{
		Matrix4x4 mat = Matrix4x4::Identity();
		mat.Scale(scale);
		mat *= rotation.GetRotationMatrix();
		mat.Translate(position);
		return mat;
	}

	void Matrix4x4::Transpose()
	{
		*this = Matrix4x4(glm::transpose(Raw()));
	}
	void Matrix4x4::Inverse()
	{
		*this = Matrix4x4(glm::inverse(Raw()));
	}
	void Matrix4x4::Scale(const Vector3& scale)
	{
		*this = Matrix4x4(glm::scale(Raw(), scale.Raw()));
	}
	void Matrix4x4::Translate(const Vector3& translation)
	{
		Vector4 position = (*this)[3];
		position.x += translation.x;
		position.y += translation.y;
		position.z += translation.z;
		(*this)[3] = position;
	}
	void Matrix4x4::Rotate(const Float32& rotation, const Float32& angle, const Vector3& axis)
	{
		*this = Matrix4x4(glm::rotate(Raw(), angle, axis));
	}
	void Matrix4x4::Rotate(const Vector3& rotation)
	{
		glm::mat4x4 mat = Raw();
		mat = glm::rotate(mat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		mat = glm::rotate(mat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		mat = glm::rotate(mat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		*this = mat;
	}
	void Matrix4x4::SetIdentity()
	{
		memset(this, 0, sizeof(Matrix4x4));
		(*this)[0][0] = 1.0f;
		(*this)[1][1] = 1.0f;
		(*this)[2][2] = 1.0f;
		(*this)[3][3] = 1.0f;
	}
	Quaternion Matrix4x4::GetRotation() const
	{
		return Quaternion(glm::quat_cast(Raw()));
	}

	glm::mat4 Matrix4x4::Raw() const
	{
		glm::mat4 mat;
		mat[0] = (*this)[0];
		mat[1] = (*this)[1];
		mat[2] = (*this)[2];
		mat[3] = (*this)[3];
		return mat;
	}

} }

#ifdef GLM_FORCE_RADIANS
#undef GLM_FORCE_RADIANS
#endif