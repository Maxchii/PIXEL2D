#pragma once
#include "Math.h"

namespace PIXL{ namespace math{

	struct Rectangle
	{
	public:
		float x, y, width, height;

		Rectangle(const float& x, const float& y, const float& width, const float& height);
		Rectangle(const Vector2f& position, const Vector2f& size);
		Rectangle(const Vector4f& dimensions);

		void Set(const float& x, const float& y, const float& width, const float& height);
		void SetPosition(const Vector2f& position);
		void SetSize(const Vector2f& size);
		float Area();
		float Perimeter();
		bool Intersects(const Rectangle& other);
		
		bool operator==(const Rectangle& other);
		bool operator!=(const Rectangle& other);
		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle);
	};

} }