#include "SpriteBatch.h"
#include "Drawable.h"
#include "SpriteBatch.h"

#include <cstddef>

namespace PIXL { namespace graphics {

	SpriteBatch::SpriteBatch() : Renderer()
	{
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_ibo = new IndexBuffer(*indices, RENDERER_INDICES_SIZE);

		m_indexCount = 0;
	}

	void SpriteBatch::Begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void SpriteBatch::Submit(Drawable* const drawable)
	{
		const math::Vector2& size = drawable->GetSize();
		const unsigned int color = drawable->GetColor();
		const std::array<math::Vector2, 4>& uvs = drawable->GetUvs();
		const GLuint tid = drawable->GetTextureID();

		*m_transformationBack = math::Matrix4x4::Translate(*m_transformationBack, math::Vector3(-(size.x * 0.5f), -(size.y * 0.5f), 1.0f));

		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			for (size_t i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
				{
					End();
					Flush();
					Begin();
				}
				m_textureSlots.push_back(tid);
				ts = (float)(m_textureSlots.size());
			}
		}

		m_buffer->vertex = *m_transformationBack * math::Vector3(0, size.y, 0);
		m_buffer->uv = uvs[3];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack * math::Vector3(size.x, size.y, 0);
		m_buffer->uv = uvs[2];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack * math::Vector3(size.x, 0, 0);
		m_buffer->uv = uvs[1];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_buffer->vertex = *m_transformationBack * math::Vector3::Zero();
		m_buffer->uv = uvs[0];
		m_buffer->tid = ts;
		m_buffer->color = color;
		m_buffer++;

		m_indexCount += 6;

		
		if (m_indexCount >= RENDERER_MAX_SPRITES * 6)
		{
			End();
			Flush();
			Begin();
		}
	}

	void SpriteBatch::SubmitLabel(const string& text, const math::Vector3& position, const Font& font, unsigned int color)
	{
		using namespace ftgl;

		float ts = 0.0f;
		bool found = false;
		for (size_t i = 0; i < m_textureSlots.size(); i++)
		{
			if (m_textureSlots[i] == font.GetID())
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
			{
				End();
				Flush();
				Begin();
			}
			m_textureSlots.push_back(font.GetID());
			ts = (float)(m_textureSlots.size());
		}

		float scaleX = 1.0f;
		float scaleY = 1.0f;

		float x = position.x;
		float y = position.y;

		texture_font_t* ftFont = font.FtFont();

		math::Matrix4x4::Translate(*m_transformationBack, math::Vector3(-x, -y, 1));

		for (size_t i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
			if (glyph != NULL)
			{

				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning;
				}

				float x0 = x + glyph->offset_x;
				float y0 = y - glyph->offset_y;

				float x1 = x0 + glyph->width;
				float y1 = y0 + glyph->height;

				float u0 = glyph->s0;
				float u1 = glyph->s1;

				float v0 = glyph->t0;
				float v1 = glyph->t1;

				m_buffer->vertex = *m_transformationBack * math::Vector3(x0, y1, 0);
				m_buffer->uv.Set(u0, v1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->vertex = *m_transformationBack * math::Vector3(x0, y0, 0);
				m_buffer->uv.Set(u0, v0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->vertex = *m_transformationBack * math::Vector3(x1, y0, 0);
				m_buffer->uv.Set(u1, v0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->vertex = *m_transformationBack * math::Vector3(x1, y1, 0);
				m_buffer->uv.Set(u1, v1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_indexCount += 6;
				x += glyph->advance_x;

				if (m_indexCount >= RENDERER_MAX_SPRITES * 6)
				{
					End();
					Flush();
					Begin();
				}
			}

		}
	}

	void SpriteBatch::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void SpriteBatch::Flush()
	{
		for (size_t i = 0; i < m_textureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
		}

		glBindVertexArray(m_vao);
		m_ibo->bind();

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);
		m_ibo->unbind();

		m_indexCount = 0;
		m_textureSlots.clear();
	}

	SpriteBatch::~SpriteBatch()
	{
		delete m_ibo;
		glDeleteBuffers(1, &m_vbo);
	}

}
}