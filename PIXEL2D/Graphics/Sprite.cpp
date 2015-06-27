#include "Sprite.h"

namespace PIXL{
	namespace graphics{

		Sprite::Sprite(Texture& texture, const math::Vector4f& color /*= math::Vector4(1.0f,1.0f,1.0f,1.0f)*/)
		{
			m_texture = &texture;
			m_size.Set((float)m_texture->Width(), (float)m_texture->Height());
			SetColor(color);
		}

		Sprite::Sprite(Texture& texture, const math::Rectangle& sourceRect, const math::Vector4f& color /*= math::Vector4(1.0f, 1.0f, 1.0f, 1.0f)*/)
		{
			m_texture = &texture;

			std::array<math::Vector2f, 4> uvCords;
			float normX = (1.0f / m_texture->Width()) * sourceRect.x;
			float normY = 1.0f - (1.0f / m_texture->Height()) * sourceRect.y;
			float normW = (1.0f / texture.Width()) * sourceRect.width;
			float normH = (1.0f / texture.Height()) * sourceRect.height;

			uvCords[0].Set(normX + normW, normY = normH);
			uvCords[1].Set(normX + normH, normY);
			uvCords[2].Set(normX, normY);
			uvCords[3].Set(normX, normY - normW);

			uvCords[0].Set(normX, normY);
			uvCords[1].Set(normX + normW, normY);
			uvCords[2].Set(normX + normW, normY - normH);
			uvCords[3].Set(normX, normY - normH);

			SetUvs(uvCords);
			m_size.Set(sourceRect.width, sourceRect.height);
			SetColor(color);
		}

		Sprite::Sprite(Texture& texture, const math::Rectangle& sourceRect, const math::Vector2f& size, const math::Vector4f& color /*= math::Vector4(1.0f, 1.0f, 1.0f, 1.0f)*/)
		{
			m_texture = &texture;

			std::array<math::Vector2f, 4> uvCords;
			float normX = (1.0f / m_texture->Width()) * sourceRect.x;
			float normY = 1.0f - (1.0f / m_texture->Height()) * sourceRect.y;
			float normW = (1.0f / texture.Width()) * sourceRect.width;
			float normH = (1.0f / texture.Height()) * sourceRect.height;

			uvCords[0].Set(normX, normY);
			uvCords[1].Set(normX + normW, normY);
			uvCords[2].Set(normX + normW, normY - normH);
			uvCords[3].Set(normX, normY - normH);

			SetUvs(uvCords);
			m_size = size;
			SetColor(color);
		}

	}
}