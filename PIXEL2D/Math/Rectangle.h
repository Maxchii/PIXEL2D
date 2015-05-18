#pragma once
#include "Math.h"

namespace PIXL{ namespace math{

	struct Rectangle
	{
	public:
		float x, y, width, height;

		Rectangle(const float& x, const float& y, const float& width, const float& height);
		Rectangle(const Vector2& position, const Vector2& size);
		Rectangle(const Vector4& dimensions);

		void Set(const float& x, const float& y, const float& width, const float& height);
		void SetPosition(const Vector2& position);
		void SetSize(const Vector2& size);
		float Area();
		float Perimeter();
		bool Intersects(const Rectangle& other);
		
		bool operator==(const Rectangle& other);
		bool operator!=(const Rectangle& other);
		friend std::ostream& operator<<(std::ostream& stream, const Rectangle& rectangle);
	};

} }