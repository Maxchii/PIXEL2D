#include "Matrix4x4.h"

namespace PIXL { namespace math {

	Matrix4x4::Matrix4x4()
	{
		for (int i = 0; i < 16; i++)
			elements[i] = 0.0f;
	}

	Matrix4x4::Matrix4x4(float diagonal)
	{
		for (int i = 0; i < 16; i++)
			elements[i] = 0.0f;

		elements[0] = diagonal;
		elements[5] = diagonal;
		elements[10] = diagonal;
		elements[15] = diagonal;
	}

	Matrix4x4 Matrix4x4::Identity()
	{
		return Matrix4x4(1.0f);
	}

	Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& other)
	{
		__declspec(align(16)) float data[16];

		/*for (unsigned int i = 0; i < 16; i += 4)
			for (unsigned int j = 0; j < 4; ++j)
				data[i + j] = (other.elements[i + 0] * elements[j + 0])
				+ (other.elements[i + 1] * elements[j + 4])
				+ (other.elements[i + 2] * elements[j + 8])
				+ (other.elements[i + 3] * elements[j + 12]);*/

		__m128 a_line, b_line, r_line;
		int i, j;
		for (i = 0; i < 16; i += 4) {
			// unroll the first step of the loop to avoid having to initialize r_line to zero
			a_line = _mm_loadu_ps(elements);         // a_line = vec4(column(a, 0))
			b_line = _mm_set1_ps(other.elements[i]);      // b_line = vec4(b[i][0])
			r_line = _mm_mul_ps(a_line, b_line); // r_line = a_line * b_line
			for (j = 1; j < 4; j++) {
				a_line = _mm_loadu_ps(&elements[j * 4]); // a_line = vec4(column(a, j))
				b_line = _mm_set1_ps(other.elements[i + j]);  // b_line = vec4(b[i][j])
				r_line = _mm_add_ps(_mm_mul_ps(a_line, b_line), r_line);
			}
			_mm_store_ps(&data[i], r_line);     // r[i] = r_line
		}

		memcpy(elements, data, 16 * sizeof(float));

		return *this;
	}

	Vector3 Matrix4x4::Multiply(const Vector3& other) const
	{
		return Vector3(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
			);
	}

	Vector4 Matrix4x4::Multiply(const Vector4& other) const
	{
		return Vector4(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			);
	}

	Matrix4x4 operator*(Matrix4x4 left, const Matrix4x4& right)
	{
		return left.Multiply(right);
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other)
	{
		return Multiply(other);
	}

	Vector3 operator*(const Matrix4x4& left, const Vector3& right)
	{
		return left.Multiply(right);
	}

	Vector4 operator*(const Matrix4x4& left, const Vector4& right)
	{
		return left.Multiply(right);
	}

	Matrix4x4& Matrix4x4::Invert()
	{
		double temp[16];

		temp[0] = elements[5] * elements[10] * elements[15] -
			elements[5] * elements[11] * elements[14] -
			elements[9] * elements[6] * elements[15] +
			elements[9] * elements[7] * elements[14] +
			elements[13] * elements[6] * elements[11] -
			elements[13] * elements[7] * elements[10];

		temp[4] = -elements[4] * elements[10] * elements[15] +
			elements[4] * elements[11] * elements[14] +
			elements[8] * elements[6] * elements[15] -
			elements[8] * elements[7] * elements[14] -
			elements[12] * elements[6] * elements[11] +
			elements[12] * elements[7] * elements[10];

		temp[8] = elements[4] * elements[9] * elements[15] -
			elements[4] * elements[11] * elements[13] -
			elements[8] * elements[5] * elements[15] +
			elements[8] * elements[7] * elements[13] +
			elements[12] * elements[5] * elements[11] -
			elements[12] * elements[7] * elements[9];

		temp[12] = -elements[4] * elements[9] * elements[14] +
			elements[4] * elements[10] * elements[13] +
			elements[8] * elements[5] * elements[14] -
			elements[8] * elements[6] * elements[13] -
			elements[12] * elements[5] * elements[10] +
			elements[12] * elements[6] * elements[9];

		temp[1] = -elements[1] * elements[10] * elements[15] +
			elements[1] * elements[11] * elements[14] +
			elements[9] * elements[2] * elements[15] -
			elements[9] * elements[3] * elements[14] -
			elements[13] * elements[2] * elements[11] +
			elements[13] * elements[3] * elements[10];

		temp[5] = elements[0] * elements[10] * elements[15] -
			elements[0] * elements[11] * elements[14] -
			elements[8] * elements[2] * elements[15] +
			elements[8] * elements[3] * elements[14] +
			elements[12] * elements[2] * elements[11] -
			elements[12] * elements[3] * elements[10];

		temp[9] = -elements[0] * elements[9] * elements[15] +
			elements[0] * elements[11] * elements[13] +
			elements[8] * elements[1] * elements[15] -
			elements[8] * elements[3] * elements[13] -
			elements[12] * elements[1] * elements[11] +
			elements[12] * elements[3] * elements[9];

		temp[13] = elements[0] * elements[9] * elements[14] -
			elements[0] * elements[10] * elements[13] -
			elements[8] * elements[1] * elements[14] +
			elements[8] * elements[2] * elements[13] +
			elements[12] * elements[1] * elements[10] -
			elements[12] * elements[2] * elements[9];

		temp[2] = elements[1] * elements[6] * elements[15] -
			elements[1] * elements[7] * elements[14] -
			elements[5] * elements[2] * elements[15] +
			elements[5] * elements[3] * elements[14] +
			elements[13] * elements[2] * elements[7] -
			elements[13] * elements[3] * elements[6];

		temp[6] = -elements[0] * elements[6] * elements[15] +
			elements[0] * elements[7] * elements[14] +
			elements[4] * elements[2] * elements[15] -
			elements[4] * elements[3] * elements[14] -
			elements[12] * elements[2] * elements[7] +
			elements[12] * elements[3] * elements[6];

		temp[10] = elements[0] * elements[5] * elements[15] -
			elements[0] * elements[7] * elements[13] -
			elements[4] * elements[1] * elements[15] +
			elements[4] * elements[3] * elements[13] +
			elements[12] * elements[1] * elements[7] -
			elements[12] * elements[3] * elements[5];

		temp[14] = -elements[0] * elements[5] * elements[14] +
			elements[0] * elements[6] * elements[13] +
			elements[4] * elements[1] * elements[14] -
			elements[4] * elements[2] * elements[13] -
			elements[12] * elements[1] * elements[6] +
			elements[12] * elements[2] * elements[5];

		temp[3] = -elements[1] * elements[6] * elements[11] +
			elements[1] * elements[7] * elements[10] +
			elements[5] * elements[2] * elements[11] -
			elements[5] * elements[3] * elements[10] -
			elements[9] * elements[2] * elements[7] +
			elements[9] * elements[3] * elements[6];

		temp[7] = elements[0] * elements[6] * elements[11] -
			elements[0] * elements[7] * elements[10] -
			elements[4] * elements[2] * elements[11] +
			elements[4] * elements[3] * elements[10] +
			elements[8] * elements[2] * elements[7] -
			elements[8] * elements[3] * elements[6];

		temp[11] = -elements[0] * elements[5] * elements[11] +
			elements[0] * elements[7] * elements[9] +
			elements[4] * elements[1] * elements[11] -
			elements[4] * elements[3] * elements[9] -
			elements[8] * elements[1] * elements[7] +
			elements[8] * elements[3] * elements[5];

		temp[15] = elements[0] * elements[5] * elements[10] -
			elements[0] * elements[6] * elements[9] -
			elements[4] * elements[1] * elements[10] +
			elements[4] * elements[2] * elements[9] +
			elements[8] * elements[1] * elements[6] -
			elements[8] * elements[2] * elements[5];

		double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];
		determinant = 1.0 / determinant;

		for (int i = 0; i < 16; i++)
			elements[i] = (float)(temp[i] * determinant);

		return *this;
	}

	Matrix4x4 Matrix4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Matrix4x4 result(1.0f);

		result.elements[0] = 2.0f / (right - left);
		result.elements[5] = 2.0f / (top - bottom);
		result.elements[10] = 2.0f / (near - far);
		result.elements[12] = (left + right) / (left - right);
		result.elements[13] = (bottom + top) / (bottom - top);
		result.elements[14] = (far + near) / (near - far);

		return result;
	}

	Matrix4x4 Matrix4x4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Matrix4x4 result(1.0f);

		float q = 1.0f / tan(ToRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0] = a;
		result.elements[5] = q;
		result.elements[10] = b;
		result.elements[11] = -1.0f;
		result.elements[14] = c;

		return result;
	}

	Matrix4x4 Matrix4x4::Translation(const Vector3& translation)
	{
		Matrix4x4 result(1.0f);

		result.elements[12] = translation.x;
		result.elements[13] = translation.y;
		result.elements[14] = translation.z;

		return result;
	}

	void Matrix4x4::Translate(const Vector3& translation)
	{
		elements[12] = translation.x;
		elements[13] = translation.y;
		elements[14] = translation.z;
	}

	Matrix4x4 Matrix4x4::Rotation(float angle, const Vector3& axis)
	{
		Matrix4x4 result(1.0f);

		float r = ToRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0] = x * omc + c;
		result.elements[1] = y * x * omc + z * s;
		result.elements[24] = x * z * omc - y * s;

		result.elements[4] = x * y * omc - z * s;
		result.elements[5] = y * omc + c;
		result.elements[6] = y * z * omc + x * s;

		result.elements[8] = x * z * omc + y * s;
		result.elements[9] = y * z * omc - x * s;
		result.elements[10] = z * omc + c;

		/*result.elements[0] = omc*x*x+c;
		result.elements[1] = omc*y*x+s*z;
		result.elements[2] = omc*z*x-s*y;

		result.elements[4] = omc*x*y-s*z;
		result.elements[5] = omc*y*y+c;
		result.elements[6] = omc*z*y+s*x;

		result.elements[8] = omc*x*z+s*y;
		result.elements[9] = omc*y*z-s*x;
		result.elements[10] = omc*z*z+c;*/

		return result;
	}

	void Matrix4x4::Rotate(float angle, const Vector3& axis)
	{
		float r = ToRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		elements[0] = x * omc + c;
		elements[1] = y * x * omc + z * s;
		elements[2] = x * z * omc - y * s;

		elements[4] = x * y * omc - z * s;
		elements[5] = y * omc + c;
		elements[6] = y * z * omc + x * s;

		elements[8] = x * z * omc + y * s;
		elements[9] = y * z * omc - x * s;
		elements[10] = z * omc + c;

		/*elements[0] = omc*x*x+c;
		elements[1] = omc*y*x+s*z;
		elements[2] = omc*z*x-s*y;

		elements[4] = omc*x*y-s*z;
		elements[5] = omc*y*y+c;
		elements[6] = omc*z*y+s*x;

		elements[8] = omc *x*z+s*y;
		elements[9] = omc*y*z-s*x;
		elements[10] = omc*z*z+c;*/
	}

	Matrix4x4 Matrix4x4::Scaled(const Vector3& scale)
	{
		Matrix4x4 result(1.0f);

		result.elements[0] = scale.x;
		result.elements[5] = scale.y;
		result.elements[10] = scale.z;

		return result;
	}

	void Matrix4x4::Scale(const Vector3& scale)
	{
		elements[0] = scale.x;
		elements[5] = scale.y;
		elements[10] = scale.z;
	}

	Matrix4x4& Matrix4x4::Transpose()
	{
		for (int i = 0; i < 16; i++) {
			for (int j = i + 1; j < 16; j++) {
				std::swap(elements[i + j], elements[j + i]);
			}
		}

		return *this;
	}
} }