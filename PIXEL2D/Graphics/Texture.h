#pragma once
#include "..//Core/ValueTypes.h"
#include <GL/glew.h>
#include <FreeImage.h>

namespace PIXL{ namespace graphics{


	enum TextureWrap
	{
		REPEAT = GL_REPEAT,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
	};

	enum TextureFilter
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
	};



	class Texture final
	{
	public:
		Texture(const string& texturePath, const TextureWrap& wrap_s, const TextureWrap& wrap_t, const TextureFilter& mag_filter, const TextureFilter& min_filter);
		~Texture();
		void Bind() const;
		void Unbind() const;

		const unsigned int ID() const;
		const unsigned int Width()const;
		const unsigned int Height()const;
	private:
		GLuint Load(const TextureWrap& wrap_s, const TextureWrap& wrap_t, const TextureFilter& mag_filter, const TextureFilter& min_filter);

	private:
		std::string m_path;
		GLuint m_textureID;
		GLsizei m_width;
		GLsizei m_height;
		unsigned int m_flags;
	};

} }
