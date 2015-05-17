#pragma once
#include "..//Core/ValueTypes.h"
#include <GL/glew.h>
#include <FreeImage.h>

namespace PIXL{ namespace graphics{

	class Texture final
	{
	public:
		Texture(const string& texturePath);
		~Texture();
		void Bind() const;
		void Unbind() const;

		const unsigned int ID() const;
		const unsigned int Width()const;
		const unsigned int Height()const;

	private:
		GLuint Load();

	private:
		std::string m_path;
		GLuint m_textureID;
		GLsizei m_width;
		GLsizei m_height;


	};

} }
