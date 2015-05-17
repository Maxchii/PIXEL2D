#pragma once
#include <GL/glew.h>

namespace PIXL {namespace graphics {

	class IndexBuffer
	{
	public:
		IndexBuffer(const GLuint& data, GLsizei count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;
		GLuint count() const;

	private:
		GLuint m_bufferID;
		GLuint m_count;
	};

} }