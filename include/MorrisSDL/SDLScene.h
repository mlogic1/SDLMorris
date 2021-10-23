#pragma once

#include "ISDLSprite.h"
#include <SDL.h>
#include <memory>
#include <vector>

class SDLScene
{
	public:
		SDLScene();
		virtual ~SDLScene() = 0;

		void Update(float dt);
		void Render(SDL_Renderer& renderer);

	protected:
		void AddSprite(std::unique_ptr<ISDLSprite> ptr);

	protected:
		virtual void InternalUpdate(float dt);
		virtual void InternalRender(SDL_Renderer& renderer);

	private:
		std::vector<std::unique_ptr<ISDLSprite>> m_sprites;
		// buttons as well
};

