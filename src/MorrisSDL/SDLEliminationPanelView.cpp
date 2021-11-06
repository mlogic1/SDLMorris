#include "SDLEliminationPanelView.h"
#include "SDLAudioLoader.h"

SDLEliminationPanelView::SDLEliminationPanelView(std::shared_ptr<SDLSprite>& panel1, std::shared_ptr<SDLSprite>& panel2) :
	m_eliminatePanelP1(panel1),
	m_eliminatePanelP2(panel2)
{
	m_panelMoveSound = SDLAudioLoader::GetInstance().LoadChunk("marker_panel_move.ogg");
}

SDLEliminationPanelView::~SDLEliminationPanelView()
{
	Mix_FreeChunk(m_panelMoveSound);
}

void SDLEliminationPanelView::Show(Morris::MorrisPlayer player)
{
	if (player == Morris::MorrisPlayer::Player1)
	{
		m_shownPanel = m_eliminatePanelP1;
	}
	else
	{
		m_shownPanel = m_eliminatePanelP2;
	}

	m_shownPanel->MoveToPosition(POSITION_SHOWN_X, POSITION_SHOWN_Y);
	Mix_PlayChannel(-1, m_panelMoveSound, 0);
}

void SDLEliminationPanelView::Hide()
{
	if (m_shownPanel)
	{
		m_shownPanel->MoveToPosition(POSITION_HIDDEN_X, POSITION_HIDDEN_Y);
		m_shownPanel = nullptr;
		Mix_PlayChannel(-1, m_panelMoveSound, 0);
	}
}
