#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <glad/glad.h>
#include <string>
#include <iostream>

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

		~ShaderProgram();

		// Deleting const of default, copying and operator =
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram &&shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

		
		// Checking compiling of OpenGL shader program
		bool isCompiled() const { return m_isCompiled; }
		
		// Checking use status of OpenGL shader program
		void use() const;

	private:
		// Functions of create shader, boolean member variable of compile status and ID of member
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}

#endif // SHADER_HEADER