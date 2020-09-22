#ifndef SPRITE_HEADER
#define SPRITE_HEADER

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>

namespace Renderer
{
	class Texture2D;

	class ShaderProgram;

	class Sprite
	{
	public:

		Sprite() = delete;

		Sprite(const std::shared_ptr<Texture2D> pTexture, 
			   const std::shared_ptr<ShaderProgram> pShaderProgram, 
			   const glm::vec2& position = glm::vec2(0.f), 
			   const glm::vec2& size = glm::vec2(0.f),
		       const float rotation = 0.f);

		Sprite(const Sprite&) = delete;

		Sprite(Sprite&&) = delete;

		Sprite& operator=(const Sprite&) = delete;

		Sprite& operator=(Sprite&&) = delete;

		~Sprite();

		void render() const;

		void setPosition(const glm::vec2& position);

		void setSize(const glm::vec2& size);

		void setRotation(const glm::vec2& size);

	private:

		std::shared_ptr<Texture2D> m_pTexture;

		std::shared_ptr<ShaderProgram> m_pShaderProgram;

		glm::vec2 m_position;

		glm::vec2 m_size;

		float m_rotation;
	};
}

#endif // SPRITE_HEADER