#include "MorrisSDL/SDLSprite.h"
#include "MorrisSDL/SDLTextureLoader.h"

SDLSprite::SDLSprite(const std::string& textureFile, SDL_Rect posAndSize) :
	m_posSize(posAndSize)
{
	m_texture = SDLTextureLoader::GetInstance().LoadImage(textureFile);

	if (!m_texture)
		throw std::string("Unable to load texture: " + textureFile);
}

SDLSprite::~SDLSprite()
{
	SDL_DestroyTexture(m_texture);
}

Uint8 SDLSprite::GetAlpha() const
{
	return m_alpha;
}

void SDLSprite::SetAlpha(Uint8 value)
{
	m_alpha = value;
	SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(m_texture, m_alpha);
}

void SDLSprite::Update(float dt)
{
	if (m_isMoving)
	{
		m_movingTimer += dt;
		m_posSize.x = Lerp(m_posSize.x, m_targetPosX);
		m_posSize.y = Lerp(m_posSize.y, m_targetPosY);

		if (std::abs(m_posSize.x - m_targetPosX) < 2 && std::abs(m_posSize.y - m_targetPosY) < 2)
		{
			CancelMoving();
			m_posSize.x = m_targetPosX;
			m_posSize.y = m_targetPosY;
		}
			
	}
}

void SDLSprite::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, m_texture, NULL, &m_posSize);
}

const SDL_Rect& SDLSprite::GetRect() const
{
	return m_posSize;
}

void SDLSprite::SetRect(const SDL_Rect& rect)
{
	m_posSize = rect;
}

void SDLSprite::SetPosition(int x, int y)
{
	m_posSize.x = x;
	m_posSize.y = y;
}

void SDLSprite::MoveToPosition(int x, int y)
{
	m_targetPosX = x;
	m_targetPosY = y;
	m_isMoving = true;
}

void SDLSprite::CancelMoving()
{
	m_isMoving = false; 
	m_movingTimer = .0f;
}

