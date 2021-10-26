#pragma once

#include "ISDLSprite.h"
#include <SDL_image.h>
#include <string>

class SDLSprite : public ISDLSprite
{
	public:
		SDLSprite(const std::string& textureFile, SDL_Rect posAndSize);
		~SDLSprite();

		Uint8 GetAlpha() const;
		void SetAlpha(Uint8 value);
		virtual void Render(SDL_Renderer& renderer) override;

	protected:
		SDL_Texture* m_texture = nullptr;
		SDL_Rect m_posSize;

		Uint8 m_alpha = 255;
};

