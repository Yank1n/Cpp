#include "ShaderProgram.h"

namespace Renderer
{
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		// Create id of Vertex shader
		GLuint vertexShaderID;

		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "Vertex shader compile time error!" << "\n";
			
			return;
		}
		
		// Create id of Fragment Vertex shader
		GLuint fragmentShaderID;
		
		// Check status of shader creation
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "Vertex shader compile time error!" << "\n";
			glDeleteShader(vertexShaderID);

			return;
		}

		// Creation of program and id of program and link vertex shader and fragment shader in program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		// Check status of linking
		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link timeout: " << infoLog << "\n";
		}
		else
		{
			m_isCompiled = true;
		}

		// Delete shaders
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}
	// Creation of shaders
	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		// Check status of shaders compiling 
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile timeout: " << infoLog << "\n";
			
			return false;
		}

		return true;
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		this->m_ID = 0;
		this->m_isCompiled = false;
	}

	// Running of shader program
	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	void ShaderProgram::setInt(const std::string& name, const int value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}
}