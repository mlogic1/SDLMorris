#pragma once

#include "SDLScene.h"
#include <SDL_mixer.h>

class SDLSceneMainMenu final : public SDLScene
{
	public:
		SDLSceneMainMenu();
		~SDLSceneMainMenu();

	protected:
		virtual void InternalUpdate(float dt) override;
		virtual void InternalRender(SDL_Renderer& renderer) override;


	private:
		Mix_Music* m_backgroundMusic = NULL;
};

