#include "SDLAnimatedSprite.h"

SDLAnimatedSprite::SDLAnimatedSprite(const std::string& textureFile, SDL_Rect posAndSize, int textureWidth, int textureHeight, float frameTime, int frameCount, int frameWidth, int frameHeight) :
	SDLSprite(textureFile, posAndSize),
	m_textureWidth(textureWidth),
	m_textureHeight(textureHeight),
	m_frameTime(frameTime),
	m_frameCount(frameCount),
	m_frameWidth(frameWidth),
	m_frameHeight(frameHeight)
{

}

SDLAnimatedSprite::~SDLAnimatedSprite()
{

}

void SDLAnimatedSprite::Update(float dt)
{
	m_currentFrametime += dt;

	if (m_currentFrametime > m_frameTime)
	{
		m_currentFrametime = .0f;
		++m_currentFrame;
		if (m_currentFrame >= m_frameCount)
			m_currentFrame = 0;

		const int frameX = m_currentFrame * m_frameWidth;
		m_srcRect.x = frameX;
	}

}

void SDLAnimatedSprite::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, m_texture, &m_srcRect, &m_posSize);
}