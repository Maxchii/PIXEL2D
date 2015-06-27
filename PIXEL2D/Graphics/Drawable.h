#pragma once
#include "..//Math/Math.h"
#include "..//Core/Component.h"
#include <array>
#include <GL/glew.h>
#include "Texture.h"
#include "Renderer.h"

namespace PIXL {namespace graphics {

	class Drawable : public Component
	{
	public:
		Drawable();
		Drawable(math::Vector2f size, const math::Vector4f& color);
		Drawable(Texture& texture, const math::Vector4f& color);
		virtual ~Drawable(){}

		void Draw(Renderer* renderer) override;

		const math::Vector2f& GetSize() const;
		const unsigned int GetColor() const;
		const std::array<math::Vector2f, 4>& GetUvs();
		const GLuint GetTextureID() const;

		const void SetSize(const math::Vector2f& newSize);
		const void SetColor(const math::Vector4f& newColor);
		void SetUvs(const std::array<math::Vector2f, 4>& newUvs);
		void SetTexture(Texture& newTexture);

	protected:
		math::Vector2f m_size;
		unsigned int m_color;
		std::array<math::Vector2f, 4> m_uvs;
		Texture* m_texture;

	private:
		const void SetUintColor(const math::Vector4f& newColor);
		const void SetDefaultUvs();
	};

} }