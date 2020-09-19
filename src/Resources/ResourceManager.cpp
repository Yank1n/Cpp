#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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

	// Creating new shader program	
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
	// Finding shader programs
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

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTextures(const std::string& textureName, const std::string texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char *pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << textureName << "\n";

		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName, std::make_shared<Renderer::Texture2D>(width, 
																															height, 
																															pixels, 
																															channels, 
																															GL_NEAREST, 
																															GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	// Finding textures
	TexturesMap::const_iterator it = m_textures.find(textureName);

	if (it != m_textures.end())
	{
		return it->second;
	}

	// or not
	std::cerr << "Can't find the shader program: " << textureName << "\n";

	return nullptr;
}