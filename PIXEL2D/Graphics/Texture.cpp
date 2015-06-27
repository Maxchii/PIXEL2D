#include "Texture.h"

namespace PIXL { namespace graphics {

	Texture::Texture(const string& texturePath, const TextureWrap& wrap_s, const TextureWrap& wrap_t, const TextureFilter& mag_filter, const TextureFilter& min_filter)
		: m_path(texturePath), m_flags(m_flags)
	{
		m_textureID = Load(wrap_s, wrap_t, mag_filter,min_filter);
	}

	GLuint Texture::Load(const TextureWrap& wrap_s, const TextureWrap& wrap_t, const TextureFilter& mag_filter, const TextureFilter& min_filter)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(m_path.c_str(), 0);
		if (fif == FIF_UNKNOWN) fif = FreeImage_GetFIFFromFilename(m_path.c_str());
		FIBITMAP* tmp = FreeImage_Load(fif, m_path.c_str());
		FIBITMAP* dib = FreeImage_ConvertTo32Bits(tmp);
		FreeImage_Unload(tmp);
		unsigned char* bits = FreeImage_GetBits(dib);
		m_width = FreeImage_GetWidth(dib);
		m_height = FreeImage_GetHeight(dib);
		unsigned long* buffer = (unsigned long*)_aligned_malloc(m_width * m_height * sizeof(unsigned long), 64);
		for (int y = 0; y < m_height; y++)
		{
			unsigned char* line = FreeImage_GetScanLine(dib, y);
			memcpy(buffer + y * m_width, line, m_width * sizeof(unsigned long));
		}
		FreeImage_Unload(dib);

		GLuint texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, buffer);

		glGenerateMipmap(GL_TEXTURE_2D);
		if (m_flags == 0 || m_flags & GL_CLAMP_TO_EDGE)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

		_aligned_free(buffer);

		return texID;
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_textureID);

	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const unsigned int Texture::ID() const
	{
		return m_textureID;
	}

	const unsigned int Texture::Width() const
	{
		return m_width;
	}

	const unsigned int Texture::Height() const
	{
		return m_height;
	}	

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}

} }