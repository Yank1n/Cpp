#ifndef RESOURCE_MANAGER_HEADER
#define RESOURCE_MANAGER_HEADER

#include <string>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>

// If you want you can link a ShaderProgram as #include "../Renderer/ShaderProgram.h
namespace Renderer
{
	class ShaderProgram;
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

private:
	// Private function for finding a file's path
	std::string getFileString(const std::string& relativeFilePath) const;
	
	// Type that contains shaders
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;

	ShaderProgramsMap m_shaderPrograms;

	// Path to Debug/
	std::string m_path;
};

#endif // RESOURCE_MANAGER_HEADER