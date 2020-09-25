#ifndef RESOURCE_MANAGER_HEADER
#define RESOURCE_MANAGER_HEADER

#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

// If you want you can link a ShaderProgram as #include "../Renderer/ShaderProgram.h
namespace Renderer
{
	class ShaderProgram;
	
	class Texture2D;

	class Sprite;
}

// Creating resource manager
class ResourceManager
{
public:
	ResourceManager(const std::string &executablePath);

	// Deleting constructors of l-value and r-value copying and operators of l-value, r-value copying
	ResourceManager(const ResourceManager&) = delete;

	ResourceManager(ResourceManager&&) = delete;

	~ResourceManager() = default;

	ResourceManager& operator=(const ResourceManager&) = delete;

	ResourceManager& operator=(ResourceManager&&) = delete;

	// Function for loading shaders from files
	std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath,
		const std::string& fragmentPath);

	// Function for getting shaders from map of shader programs
	std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);

	// Function for loading textures from files
	std::shared_ptr<Renderer::Texture2D> loadTextures(const std::string& textureName, const std::string texturePath);

	// Function for getting textures from map of shader programs
	std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

	std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName, const std::string &textureName, 
												 const std::string &shaderName, const unsigned int spriteWidth, 
												 const unsigned int spriteHeight,
												 const std::string& subTextureName = "default");

	std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string& subTextureName,
														  const std::string subTexturePath,
														  const std::vector<std::string> subTexture,
														  const unsigned int subTextureWidth,
														  const unsigned int subTextureHeight);

	std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

private:
	// Private function for finding a file's path
	std::string getFileString(const std::string& relativeFilePath) const;
	
	// Type that contains shaders
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;

	TexturesMap m_textures;

	ShaderProgramsMap m_shaderPrograms;

	SpritesMap m_sprites;

	// Path to Debug/
	std::string m_path;
};

#endif // RESOURCE_MANAGER_HEADER