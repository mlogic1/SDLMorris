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

void SDLSprite::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, m_texture, NULL, &m_posSize);
}

