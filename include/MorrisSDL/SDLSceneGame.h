#pragma once

#include "SDLScene.h"
#include <SDL_mixer.h>
#include "SDLMarkerView.h"
#include "SDLMarkerViewMover.h"
#include "MorrisGame/MorrisGame.h"
#include <memory>

class SDLSceneGame final : public SDLScene
{
	public:
		SDLSceneGame(SDLWindow& window);
		~SDLSceneGame();

	private:
		virtual void InternalUpdate(float dt) override;
		virtual void InternalRender(SDL_Renderer& renderer) override;

		virtual void InternalOnMousePressed(Uint8 button) override;
		virtual void InternalOnMouseReleased(Uint8 button)  override;

	private:
		Mix_Music* m_backgroundMusic = nullptr;

		std::vector<std::unique_ptr<SDLMarkerView>> markers;

	private:
		// game backend
		std::unique_ptr<Morris::MorrisGame> m_game;

		std::unique_ptr<SDLMarkerViewMover> m_markerViewMover;
		std::vector<std::shared_ptr<SDLMarkerView>> m_markerViews;
};

