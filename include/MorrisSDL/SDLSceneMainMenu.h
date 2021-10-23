#pragma once

#include "SDLScene.h"

class SDLSceneMainMenu final : public SDLScene
{
	public:
		SDLSceneMainMenu();
		~SDLSceneMainMenu();

	protected:
		virtual void InternalUpdate(float dt) override;
		virtual void InternalRender(SDL_Renderer& renderer) override;
};

