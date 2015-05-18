#include "Vector4.h"

namespace PIXL { namespace math {

	Vector4::Vector4(const float& x, const float& y, const float& z, const float& w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vector4::Set(const float& x, const float& y, const float& z, const float& w)
{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4& Vector4::Add(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vector4& Vector4::Subtract(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vector4& Vector4::Multiply(const Vector4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	Vector4& Vector4::Divide(const Vector4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	float Vector4::Length()
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	void Vector4::Normalize()
	{
		float length = this->Length();

		if (length != 0)
		{
			x = x / length;
			y = y / length;
			z = z / length;
			w = w / length;
		}
	}

	PIXL::math::Vector4 Vector4::Normalized()
	{
		Vector4 vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
			vector.w = w / length;
		}

		return vector;
	}

	void Vector4::Invert()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	PIXL::math::Vector4 Vector4::Inverted()
	{
		Vector4 temp;
		temp.x = -x;
		temp.y = -y;
		temp.z = -z;
		temp.w = -w;
		return temp;
	}

	float Vector4::Distance(const Vector4& other)
	{
		return sqrt(
			pow((x - other.x), 2)
			+ pow((y - other.y), 2)
			+ pow((z - other.z), 2)
			+ pow((w - other.w), 2));

	}

	float Vector4::Magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
	}

	float Vector4::Dot(const Vector4& a, const Vector4& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}

	PIXL::math::Vector4 Vector4::Lerp(const Vector4& from, const Vector4& to, float t)
	{
		Vector4 temp;
		temp.x = from.x + (to.x - from.x) * t;
		temp.y = from.y + (to.y - from.y) * t;
		temp.z = from.z + (to.z - from.z) * t;
		temp.w = from.w + (to.w - from.w) * t;
		return temp;
	}

	Vector4 operator+(Vector4 left, const Vector4& right)
	{
		return left.Add(right);
	}

	Vector4 operator-(Vector4 left, const Vector4& right)
	{
		return left.Subtract(right);
	}

	Vector4 operator*(Vector4 left, const Vector4& right)
	{
		return left.Multiply(right);
	}

	Vector4 operator/(Vector4 left, const Vector4& right)
	{
		return left.Divide(right);
	}

	Vector4& Vector4::operator+=(const Vector4& other)
	{
		return Add(other);
	}

	Vector4& Vector4::operator-=(const Vector4& other)
	{
		return Subtract(other);
	}

	Vector4& Vector4::operator*=(const Vector4& other)
	{
		return Multiply(other);
	}

	Vector4& Vector4::operator/=(const Vector4& other)
	{
		return Divide(other);
	}

	bool Vector4::operator==(const Vector4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool Vector4::operator!=(const Vector4& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4& vector)
	{
		return stream << "Vector4 [" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << "]";
	}
} }