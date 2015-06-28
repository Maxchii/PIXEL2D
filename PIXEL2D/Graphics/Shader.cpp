#include "shader.h"
#include "..//Debugging/Debug.h"
#include <vector>

namespace PIXL{ namespace graphics{

	Shader::Shader(const char* vertPath, const char* fragPath)
		: m_vertPath(vertPath), m_fragPath(fragPath)
	{
		m_shaderID = Load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

	GLuint Shader::Load()
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertSourceString = utilities::ReadTextFromFile(m_vertPath);
		std::string fragSourceString = utilities::ReadTextFromFile(m_fragPath);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			string errorString = "Failed to compile vertex shader!\n--> ";
			errorString.append(&error[0]);
			debugging::Debug::LogError(nullptr, errorString.c_str());
			glDetachShader(program, vertex);
			glDeleteShader(vertex);
			return 0;
		}

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			string errorString = "Failed to compile fragment shader!\n--> ";
			errorString.append(&error[0]);
			debugging::Debug::LogError(nullptr, errorString.c_str());
			glDetachShader(program, fragment);
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	GLint Shader::GetUniformLocation(const GLchar* name)
	{
		if (m_locationCache.find(name) != m_locationCache.end())
			return m_locationCache[name];

		GLint location = glGetUniformLocation(m_shaderID, name);
		m_locationCache[name] = location;
		return location;
	}

	void Shader::SetUniform1f(const GLchar* name, Float32 value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1fv(const GLchar* name, Float32* value, int count)
	{
		glUniform1fv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform1i(const GLchar* name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1iv(const GLchar* name, int* value, int count)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}

	void Shader::SetUniform2f(const GLchar* name, const math::Vector2f& vector)
	{
		glUniform2f(GetUniformLocation(name), vector.x, vector.y);
	}

	void Shader::SetUniform3f(const GLchar* name, const math::Vector3f& vector)
	{
		glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::SetUniform4f(const GLchar* name, const math::Vector4f& vector)
	{
		glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::SetUniformMat4(const GLchar* name, const math::Matrix4x4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, matrix.elements);
	}

	void Shader::Enable() const
	{
		glUseProgram(m_shaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(0);
	}

	GLuint Shader::ID()
	{
		return m_shaderID;
	}

} }