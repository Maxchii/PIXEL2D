#include "Drawable.h"

namespace PIXL { namespace graphics{

	Drawable::Drawable()
		: m_size(math::Vector2(1.0f, 1.0f)), m_color(0xffffff) {}

	Drawable::Drawable(math::Vector2 size, const math::Vector4& color)
		: m_size(size), m_texture(nullptr)
	{
		SetDefaultUvs();
		SetUintColor(color);
	}

	Drawable::Drawable(Texture& texture, const math::Vector4& color)
		: m_texture(&texture)
	{
		SetDefaultUvs();
		SetUintColor(color);
		m_size.Set((float)m_texture->Width(), (float)m_texture->Height());
	}

	void Drawable::Draw(graphics::Renderer* renderer)
	{
		renderer->Submit(this);
	}

	const math::Vector2& Drawable::GetSize() const
	{
		return m_size;
	}

	const unsigned int Drawable::GetColor() const
	{
		return m_color;
	}

	const GLuint Drawable::GetTextureID() const
	{
		return m_texture ? m_texture->ID() : 0;
	}

	const void Drawable::SetSize(const math::Vector2& newSize)
	{
		m_size = newSize;
	}

	const void Drawable::SetColor(const math::Vector4& newColor)
	{
		SetUintColor(newColor);
	}

	void Drawable::SetUvs(const std::array<math::Vector2, 4>& newUvs)
	{
		m_uvs = newUvs;
	}

	const std::array<math::Vector2, 4>& Drawable::GetUvs()
	{
		return m_uvs;
	}

	void Drawable::SetTexture(Texture& newTexture)
	{
		m_texture = &newTexture;
	}

	const void Drawable::SetUintColor(const math::Vector4& newColor)
	{
		unsigned int color = 0;
		int r = (int)(newColor.x * 255.0f);
		int g = (int)(newColor.y * 255.0f);
		int b = (int)(newColor.z * 255.0f);
		int a = (int)(newColor.w * 255.0f);
		m_color = a << 24 | b << 16 | g << 8 | r;
	}

	const void Drawable::SetDefaultUvs()
	{
		m_uvs[0] = math::Vector2(0, 1);
		m_uvs[1] = math::Vector2(1, 1);
		m_uvs[2] = math::Vector2(1, 0);
		m_uvs[3] = math::Vector2(0, 0);
	}

}
}