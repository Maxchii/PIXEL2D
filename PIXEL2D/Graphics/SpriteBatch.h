#pragma once
#include "Renderer.h"
#include "IndexBuffer.h"
#include "Drawable.h"
#include <GL/glew.h>

namespace PIXL { namespace graphics {

#define RENDERER_MAX_SPRITES	65535
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	struct VertexData
	{
		math::Vector3f vertex;
		math::Vector2f uv;
		float tid;
		unsigned int color;
	};

	class SpriteBatch final : public graphics::Renderer
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Begin() override;
		void Submit(Drawable*const  drawable);
		void SubmitLabel(const string& text, const math::Vector3f& position, const Font& font, unsigned int color) override;
		void End() override;
		void Flush() override;

	private:
		GLuint m_vao;
		GLuint m_vbo;
		IndexBuffer* m_ibo;
		GLsizei m_indexCount;
		VertexData* m_buffer;
		std::vector<GLuint> m_textureSlots;
	};

} }