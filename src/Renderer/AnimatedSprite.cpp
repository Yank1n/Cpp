#include "AnimatedSprite.h"
#include "Texture2D.h"

namespace Renderer
{
	AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2D> pTexture,
		const std::string initialSubTexture,
		const std::shared_ptr<ShaderProgram> pShaderProgram,
		const glm::vec2& position = glm::vec2(0.f),
		const glm::vec2& size = glm::vec2(1.f),
		const float rotation = 0.f)
		: Sprite(std::move(pTexture), std::move(initialSubTexture), std::move(pShaderProgram), position, size, rotation) 
	{
		m_pCurrentAnimationDuration = m_stateMap.end();
	}

	void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
	{
		m_stateMap.emplace(std::move(state), std::move(subTexturesDuration));
	}

	

	void AnimatedSprite::setState(const std::string& newState)
	{
		auto it = m_stateMap.find(newState);
		if (it != m_stateMap.end())
		{
			std::cerr << "Can't find " << newState << " animation state!\n";

			return; 
		}

		if (it != m_pCurrentAnimationDuration)
		{
			m_currentAnimationTime = 0;

			m_currentFrame = 0;

			m_pCurrentAnimationDuration = it;
		}
	}

	void AnimatedSprite::update(const size_t delta)
	{
		if (m_pCurrentAnimationDuration != m_stateMap.end())
		{
			m_currentAnimationTime += delta;

			while (m_currentFrame >= m_pCurrentAnimationDuration->second[m_currentFrame].second)
			{
				m_currentAnimationTime -= m_pCurrentAnimationDuration->second[m_currentFrame].second;

				++m_currentFrame;
			}

			if (m_currentFrame == m_pCurrentAnimationDuration->second.size())
			{
				m_currentFrame = 0;
			}
		}
	}

	void AnimatedSprite::render() const
	{
		auto subTexture = pTexture->getSubTexture(std::move(m_pCurrentAnimationDuration->second[m_currentFrame].first));

		const GLfloat textureCoords[]
		{
			//U  V
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,

			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
		};
	}
}