#include "SDLEndGamePanelView.h"
#include "SDLAudioLoader.h"

SDLEndGamePanelView::SDLEndGamePanelView(std::shared_ptr<SDLSprite>& p1winPanel, std::shared_ptr<SDLSprite>& p2winPanel, std::shared_ptr<SDLButton>& btnPlayAgain, std::shared_ptr<SDLButton>& btnBackToMenu, std::shared_ptr<SDLButton>& btnQuit) :
	m_p1WinPanel(p1winPanel),
	m_p2WinPanel(p2winPanel),
	m_buttonPlayAgain(btnPlayAgain),
	m_buttonBackToMenu(btnBackToMenu),
	m_buttonQuit(btnQuit)
{
	m_p1WinPanel->SetAlpha(0);
	m_p2WinPanel->SetAlpha(0);

	m_buttonPlayAgain->SetVisible(false);
	m_buttonBackToMenu->SetVisible(false);
	m_buttonQuit->SetVisible(false);

	m_panelShowSound = SDLAudioLoader::GetInstance().LoadChunk("victory.ogg");
}

SDLEndGamePanelView::~SDLEndGamePanelView()
{
	Mix_FreeChunk(m_panelShowSound);
}

void SDLEndGamePanelView::Show(Morris::MorrisPlayer winner)
{
	if (winner == Morris::MorrisPlayer::Player1)
	{
		m_shownPanel = m_p1WinPanel;
	}
	else
	{
		m_shownPanel = m_p2WinPanel;
	}

	m_shownPanel->SetAlpha(255);
	m_buttonPlayAgain->SetVisible(true);
	m_buttonBackToMenu->SetVisible(true);
	m_buttonQuit->SetVisible(true);

	Mix_PlayChannel(-1, m_panelShowSound, 0);
}

void SDLEndGamePanelView::Hide()
{
	if (m_shownPanel)
	{
		m_shownPanel->SetAlpha(0);
		m_buttonPlayAgain->SetVisible(false);
		m_buttonBackToMenu->SetVisible(false);
		m_buttonQuit->SetVisible(false);
	}
		
	m_shownPanel = nullptr;
}
