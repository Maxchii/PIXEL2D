#pragma once
#include "..//Math/Math.h"
#include "Texture.h"
#include "Drawable.h"


namespace PIXL {
	namespace graphics {

		struct Sprite : public Drawable
		{
		public:
			Sprite(Texture& texture, const math::Vector4f& color = math::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
			Sprite(Texture& texture, const math::Rectangle& sourceRect, const math::Vector4f& color = math::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
			Sprite(Texture& texture, const math::Rectangle& sourceRect, const math::Vector2f& size, const math::Vector4f& color = math::Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

		};

	}
}