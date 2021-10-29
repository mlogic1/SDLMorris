#pragma once

#include "SDLScene.h"
#include "SDLMarkerView.h"
#include "SDLMarkerViewMode.h"
#include "SDLMarkerViewMover.h"
#include "SDLMarkerViewEliminatorController.h"
#include "SDLEliminationPanelView.h"
#include "MorrisGame/MorrisGame.h"
#include <SDL_mixer.h>
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

		bool OnTryMoveMarker(const SDLMarkerView& markerView, int pos);
		bool OnTryEliminateMarker(const Morris::MorrisMarkerPtr marker);

		// callbacks from backend
		void OnPlayerTurnChanged(Morris::MorrisPlayer player);
		void OnGameStateChanged(Morris::MorrisGameState previousState, Morris::MorrisGameState newState);
		void OnPlayerWin(Morris::MorrisPlayer winningPlayer);

		void OnMarkerEliminated(const Morris::MorrisMarkerPtr marker);
		void OnMarkerPlaced(int pos, const Morris::MorrisMarkerPtr marker);
		void OnMarkerMoved(int pos, const Morris::MorrisMarkerPtr marker);

	private:
		Mix_Music* m_backgroundMusic = nullptr;

		std::vector<std::unique_ptr<SDLMarkerView>> markers;

	private:
		// game backend
		std::unique_ptr<Morris::MorrisGame> m_game;

		std::unique_ptr<SDLMarkerViewMover> m_markerViewMover;
		std::unique_ptr<SDLMarkerViewEliminatorController> m_eliminatorViewController;
		std::unique_ptr<SDLEliminationPanelView> m_eliminationPanel;
		std::vector<std::shared_ptr<SDLMarkerView>> m_markerViews;

		MarkerViewMode m_markerMode = MarkerViewMode::Grabbing;
};

