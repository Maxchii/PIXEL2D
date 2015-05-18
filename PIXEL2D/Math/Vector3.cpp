#include "Vector3.h"

namespace PIXL { namespace math {

	Vector3::Vector3(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3::Set(const float& x, const float& y, const float& z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3& Vector3::Add(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3& Vector3::Subtract(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3& Vector3::Multiply(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vector3& Vector3::Divide(const Vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}


	float Vector3::Length()
	{
		return sqrt(x * x + y * y + z * z);
	}

	PIXL::math::Vector3 Vector3::Normalized()
	{
		Vector3 vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}

		return vector;
	}

	void Vector3::Normalize()
	{
		float length = this->Length();

		if (length != 0)
		{
			x = x / length;
			y = y / length;
			z = z / length;
		}
	}

	void Vector3::Invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	Vector3 Vector3::Inverted()
	{
		Vector3 temp;
		temp.x = -x;
		temp.y = -y;
		temp.z = -z;
		return temp;
	}

	float Vector3::Distance(const Vector3& other)
	{
		return sqrt(pow((x - other.x), 2) + pow((y - other.y), 2) + pow((z - other.z), 2));
	}

	float Vector3::Magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	PIXL::math::Vector3 Vector3::Lerp(const Vector3& from, const Vector3& to, float t)
	{
		Vector3 temp;
		temp.x = from.x + (to.x - from.x) * t;
		temp.y = from.y + (to.y - from.y) * t;
		temp.z = from.z + (to.z - from.z) * t;
		return temp;
	}

	Vector3 operator+(Vector3 left, const Vector3& right)
	{
		return left.Add(right);
	}

	Vector3 operator-(Vector3 left, const Vector3& right)
	{
		return left.Subtract(right);
	}

	Vector3 operator*(Vector3 left, const Vector3& right)
	{
		return left.Multiply(right);
	}

	Vector3 operator/(Vector3 left, const Vector3& right)
	{
		return left.Divide(right);
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		return Add(other);
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		return Subtract(other);
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		return Multiply(other);
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		return Divide(other);
	}

	bool Vector3::operator==(const Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3& vector)
	{
		return stream << "Vector3 [" << vector.x << "," << vector.y << "," << vector.z << "]";
	}


} }