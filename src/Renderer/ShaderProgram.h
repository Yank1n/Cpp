#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>

namespace Renderer
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		
		// Deleting constructors of default and l-value copying 
		ShaderProgram() = delete;

		ShaderProgram(ShaderProgram&) = delete;

		~ShaderProgram();

		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

		// Deleting operator of copying l-value		
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		// Checking compiling of OpenGL shader program
		bool isCompiled() const { return m_isCompiled; }
		
		// Checking use status of OpenGL shader program
		void use() const;

		void setInt(const std::string& name, const int value);

		void setMatrix4(const std::string& name, const glm::mat4& matrix);
		
	private:
		// Functions of create shader, boolean member variable of compile status and ID of member
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}

#endif // SHADER_HEADER