#include "Texture.h"

namespace PIXL { namespace graphics {

	Texture::Texture(const string& texturePath)
		: m_path(texturePath)
	{
		m_textureID = Load();
	}

	GLuint Texture::Load()
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP* dib = nullptr;
		fif = FreeImage_GetFileType(m_path.c_str(), 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(m_path.c_str());
		if (fif == FIF_UNKNOWN)
			return 0;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, m_path.c_str());
		if (!dib)
			return 0;

		BYTE* pixels = FreeImage_GetBits(dib);
		m_width = FreeImage_GetWidth(dib);
		m_height = FreeImage_GetHeight(dib);
		int bits = FreeImage_GetBPP(dib);

		int size = m_width * m_height * (bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		//TODO Find out why big images don't work or result in a white screen

		GLuint texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, result);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		delete[] result;

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

}
}