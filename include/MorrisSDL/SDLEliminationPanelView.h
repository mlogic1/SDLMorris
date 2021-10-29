#pragma once

#include "SDLSprite.h"
#include <SDL_mixer.h>
#include "MorrisGame/MorrisPlayer.h"
#include <string>
#include <memory>

class SDLEliminationPanelView
{
	public:
		SDLEliminationPanelView(std::shared_ptr<SDLSprite>& panel1, std::shared_ptr<SDLSprite>& panel2);
		~SDLEliminationPanelView();

		void Show(Morris::MorrisPlayer player);
		void Hide();

	private:
		bool m_isShown = false;

		std::shared_ptr<SDLSprite> m_eliminatePanelP1;
		std::shared_ptr<SDLSprite> m_eliminatePanelP2;

		std::shared_ptr<SDLSprite> m_shownPanel = nullptr;
		Mix_Chunk* m_panelMoveSound = nullptr;

		static constexpr int POSITION_SHOWN_X = 1030;
		static constexpr int POSITION_SHOWN_Y = 515;
		static constexpr int POSITION_HIDDEN_X = 1285;
		static constexpr int POSITION_HIDDEN_Y = 515;
};