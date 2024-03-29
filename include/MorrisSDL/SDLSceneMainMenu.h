#pragma once

#include "SDLScene.h"
#include <SDL_mixer.h>
#include <memory>

class SDLSceneMainMenu final : public SDLScene
{
	public:
		SDLSceneMainMenu(SDLWindow& window);
		~SDLSceneMainMenu();

	private:
		virtual void InternalUpdate(float dt) override;
		virtual void InternalRender(SDL_Renderer& renderer) override;

	private:
		void OnPlayButtonPressed();
		void OnQuitButtonPressed();

	private:
		Mix_Music* m_backgroundMusic = nullptr;
};

