#pragma once
#include <map>
#include <GL/glew.h>
#include "..//Math/Math.h"
#include "..//Utilities/FileUtilities.h"
#include "..//Core/ValueTypes.h"

namespace PIXL{ namespace graphics{

		class Shader
		{
		public:
			Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
			~Shader();

			GLuint ID();
			void Enable() const;
			void Disable() const;

			void SetUniform1f(const GLchar* name, Float32 value);
			void SetUniform1fv(const GLchar* name, Float32* value, int count);
			void SetUniform1i(const GLchar* name, int value);
			void SetUniform1iv(const GLchar* name, int* value, int count);
			void SetUniform2f(const GLchar* name, const math::Vector2f& vector);
			void SetUniform3f(const GLchar* name, const math::Vector3f& vector);
			void SetUniform4f(const GLchar* name, const math::Vector4f& vector);
			void SetUniformMat4(const GLchar* name, const math::Matrix4x4& matrix);

		private:
			GLuint Load();
			GLint GetUniformLocation(const GLchar* name);
		private:
			const char* m_vertPath;
			const char* m_fragPath;
			GLuint m_shaderID;
			std::map<const GLchar*, GLint> m_locationCache;
		};

	}
}