#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");

	// Contains path to Debug/
	m_path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath,
	const std::string& fragmentPath)
{
	// Contains relative path to vertex.txt
	std::string vertexString{ getFileString(vertexPath) };

	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!\n";

		return nullptr;
	}

	// Contains relative path to fragment.txt
	std::string fragmentString{ getFileString(fragmentPath) };

	if (vertexString.empty())
	{
		std::cerr << "No fragment shader!\n";

		return nullptr;
	}

	// Getting pointer to all shaders
	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

	// Check that it compiles
	if (newShader->isCompiled())
	{
		return newShader;
	}
	
	// if not
	std::cerr << "Can't load shader program:\n"
		<< "Vertex: " << vertexPath
		<< "\nFragment:" << fragmentPath << "\n";

	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	// Finding all shader programs
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);

	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}

	// or not
	std::cerr << "Can't find the shader program: " << shaderName << "\n";

	return nullptr;
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::ifstream f;

	// Finding a files: vertex/fragment.txt
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed open file: " << relativeFilePath << "\n";

		return std::string{ "" };
	}

	std::stringstream buffer;

	buffer << f.rdbuf();

	// return decoded string
	return buffer.str();
}