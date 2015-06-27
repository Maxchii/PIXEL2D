#include "Rectangle.h"

namespace PIXL{ namespace math{

	Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	Rectangle::Rectangle(const Vector2f& position, const Vector2f& size)
	{
		x = position.x;
		y = position.y;
		width = size.x;
		height = size.y;
	}

	Rectangle::Rectangle(const Vector4f& dimensions)
	{
		x = dimensions.x;
		y = dimensions.y;
		width = dimensions.z;
		height = dimensions.w;
	}

	void Rectangle::Set(const float& x, const float& y, const float& width, const float& height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	void Rectangle::SetPosition(const Vector2f& position)
	{
		x = position.x;
		y = position.y;
	}

	void Rectangle::SetSize(const Vector2f& size)
	{
		width = size.x;
		height = size.y;
	}

	float Rectangle::Area()
	{
		return width * height;
	}

	float Rectangle::Perimeter()
	{
		return (2 * width + 2 * height);
	}

	bool Rectangle::Intersects(const Rectangle& other)
	{
		return !(other.x > (x + width) || (other.x + other.width) < x ||
			other.y > (y +height)|| (other.y + other.height) < y);
	}

	bool Rectangle::operator==(const Rectangle& other)
	{
		return x == other.x && y == other.y && width == other.width && height == other.height;
	}

	bool Rectangle::operator!=(const Rectangle& other)
	{
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle)
	{
		stream << "Rectangle: (" << rectangle.x << ", " << rectangle.y << ", " << rectangle.width << ", " << rectangle.height << ")";
		return stream;
	}
}
}