#include "Vector2.h"

namespace PIXL { namespace math {

	Vector2::Vector2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	void Vector2::Set(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2& Vector2::Add(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2& Vector2::Subtract(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2& Vector2::Multiply(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vector2& Vector2::Divide(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vector2 operator+(Vector2 left, const Vector2& right)
	{
		return left.Add(right);
	}

	Vector2 operator-(Vector2 left, const Vector2& right)
	{
		return left.Subtract(right);
	}

	Vector2 operator*(Vector2 left, const Vector2& right)
	{
		return left.Multiply(right);
	}

	Vector2 operator/(Vector2 left, const Vector2& right)
	{
		return left.Divide(right);
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		return Add(other);
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		return Subtract(other);
	}

	Vector2& Vector2::operator*=(const Vector2& other)
	{
		return Multiply(other);
	}

	Vector2& Vector2::operator/=(const Vector2& other)
	{
		return Divide(other);
	}

	void Vector2::Normalize()
	{
		float length = this->Length();

		if (length != 0)
		{
			x = x / length;
			y = y / length;
		}
	}

	Vector2 Vector2::Normalized()
	{
		Vector2 vector;
		float length = this->Length();

		if (length != 0){
			vector.x = x / length;
			vector.y = y / length;
		}

		return vector;
	}

	float Vector2::Length()
	{
		return sqrt(x * x + y * y);
	}

	void Vector2::Invert()
	{
		x = -x;
		y = -y;
	}

	Vector2 Vector2::Inverted()
	{
		Vector2 temp;
		temp.x = -x;
		temp.y = -y;
		return temp;
	}

	float Vector2::Distance(const Vector2& other)
	{
		return sqrt(pow((x - other.x), 2) + pow((y - other.y), 2));
	}

	float Vector2::Magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	Vector2 Vector2::Lerp(const Vector2& from, const Vector2& to, float t)
	{
		Vector2 temp;
		temp.x = from.x + (to.x - from.x) * t;
		temp.y = from.y + (to.y - from.y) * t;
		return temp;
	}

	bool Vector2::operator==(const Vector2& other)
	{
		return x == other.x && y == other.y;
	}

	bool Vector2::operator!=(const Vector2& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		return stream << "Vector2 [" << vector.x << "," << vector.y << "]";
	}


} }