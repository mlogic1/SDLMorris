#pragma once

#include "SDLSprite.h"
#include "SDLButton.h"
#include "MorrisGame/MorrisPlayer.h"
#include <SDL_mixer.h>
#include <memory>

class SDLEndGamePanelView
{
public:
	SDLEndGamePanelView(std::shared_ptr<SDLSprite>& p1winPanel, std::shared_ptr<SDLSprite>& p2winPanel, std::shared_ptr<SDLButton>& btnPlayAgain, std::shared_ptr<SDLButton>& btnBackToMenu, std::shared_ptr<SDLButton>& btnQuit);
	~SDLEndGamePanelView();

	void Show(Morris::MorrisPlayer winner);
	void Hide();

private:
	bool m_isShown = false;

	std::shared_ptr<SDLSprite> m_p1WinPanel;
	std::shared_ptr<SDLSprite> m_p2WinPanel;

	std::shared_ptr<SDLButton> m_buttonPlayAgain;
	std::shared_ptr<SDLButton> m_buttonBackToMenu;
	std::shared_ptr<SDLButton> m_buttonQuit;

	std::shared_ptr<SDLSprite> m_shownPanel = nullptr;
	Mix_Chunk* m_panelShowSound = nullptr;
};