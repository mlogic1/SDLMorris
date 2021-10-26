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

void SDLSprite::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, m_texture, NULL, &m_posSize);
}

