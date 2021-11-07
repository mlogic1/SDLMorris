#include "SDLSceneGame.h"
#include "SDLTextureLoader.h"
#include "SDLAudioLoader.h"

SDLSceneGame::SDLSceneGame(SDLWindow& window) :
	SDLScene(window)
{
	SDL_Rect rectBG = {0, 0, 1280, 800};
	SDL_Rect boardRect = { 290, 50, 700, 700 };
	
	AddSprite(std::make_unique<SDLSprite>("menu.png", rectBG));
	AddSprite(std::make_unique<SDLSprite>("board.png", boardRect));

	m_backgroundMusic = SDLAudioLoader::GetInstance().LoadMusic("menubgm.ogg");

	m_game = std::make_unique<Morris::MorrisGame>(this);

	const std::vector<Morris::MorrisMarkerPtr>& allMarkers = m_game->GetUnplacedMarkers();

	SDL_Rect whitePos = { 50, 15, 85, 85 };
	SDL_Rect blackPos = { 1050, 15, 85, 85 };
	int whiteInstanceCount = 0;
	int blackInstanceCount = 0;

	std::string textureName;
	std::shared_ptr<SDLMarkerView> markerView;
	for (const Morris::MorrisMarkerPtr& marker : allMarkers)
	{
		switch (marker->GetColor())
		{
		case Morris::MorrisPlayer::Player1:
		{
			textureName = "marker_white.png";
			markerView = std::make_shared<SDLMarkerView>(textureName, whitePos, marker);
			whitePos.y += 100;
			++whiteInstanceCount;
			if (whiteInstanceCount >= 5)
			{
				whitePos.x += 100;
				whitePos.y = 15;
				whiteInstanceCount = 0;
			}
			break;
		}

		case Morris::MorrisPlayer::Player2:
		{
			textureName = "marker_black.png";
			markerView = std::make_shared<SDLMarkerView>(textureName, blackPos, marker);
			blackPos.y += 100;
			++blackInstanceCount;
			if (blackInstanceCount >= 5)
			{
				blackPos.x += 100;
				blackPos.y = 15;
				blackInstanceCount = 0;
			}
			break;
		}
		default:
			break;
		}
		m_markerViews.emplace_back(std::move(markerView));
	}

	m_markerViewMover = std::make_unique<SDLMarkerViewMover>(m_markerViews, m_markerMode, std::bind(&SDLSceneGame::OnTryMoveMarker, this, std::placeholders::_1, std::placeholders::_2));
	std::shared_ptr<SDLSprite> markerEliminatorSprite = std::make_shared<SDLSprite>("marker_eliminate.png", SDL_Rect{ -150, -150, 104, 103 });
	m_eliminatorViewController = std::make_unique<SDLMarkerViewEliminatorController>(markerEliminatorSprite, *m_game, m_markerMode, std::bind(&SDLSceneGame::OnTryEliminateMarker, this, std::placeholders::_1));
	std::shared_ptr<SDLSprite> eliminatePanelP1 = std::make_shared<SDLSprite>("marker_eliminate_black.png", SDL_Rect{ 1285, 515, 226, 273 });
	std::shared_ptr<SDLSprite> eliminatePanelP2 = std::make_shared<SDLSprite>("marker_eliminate_white.png", SDL_Rect{ 1285, 515, 226, 273 });

	m_eliminationPanel = std::make_unique<SDLEliminationPanelView>(eliminatePanelP1, eliminatePanelP2);
	
	for (auto hitbox : m_markerViewMover->GetHitboxes())
	{
		AddSprite(hitbox);
		hitbox->SetAlpha(0);
	}

	for (auto markerView : m_markerViews)
	{
		AddSprite(markerView);
	}
	
	AddSprite(markerEliminatorSprite);
	AddSprite(eliminatePanelP1);
	AddSprite(eliminatePanelP2);

	// end game dialog content
	std::shared_ptr<SDLSprite> endPanelp1 = std::make_shared<SDLSprite>("dialog_end_p1_wins.png", SDL_Rect{ 404, 152, 473, 496 });
	std::shared_ptr<SDLSprite> endPanelp2 = std::make_shared<SDLSprite>("dialog_end_p2_wins.png", SDL_Rect{ 404, 152, 473, 496 });

	std::shared_ptr<SDLButton> btnPlayAgain = std::make_shared<SDLButton>(SDL_Rect{ 488, 315, 304, 85 }, "play_again_idle.png", "play_again_hover.png", "play_again_pressed.png", std::bind(&SDLSceneGame::OnPlayAgainClick, this), "hover.ogg", "action_success.ogg");
	std::shared_ptr<SDLButton> btnBackToMenu = std::make_shared<SDLButton>(SDL_Rect{ 488, 420, 304, 85 }, "back_to_menu_idle.png", "back_to_menu_hover.png", "back_to_menu_pressed.png", std::bind(&SDLSceneGame::OnBackToMenuClick, this), "hover.ogg", "action_success.ogg");
	std::shared_ptr<SDLButton> btnQuit = std::make_shared<SDLButton>(SDL_Rect{ 488, 510, 304, 85 }, "quit2_idle.png", "quit2_hover.png", "quit2_pressed.png", std::bind(&SDLSceneGame::OnQuitClick, this), "hover.ogg", "action_success.ogg");

	m_endGamePanelView = std::make_unique<SDLEndGamePanelView>(endPanelp1, endPanelp2, btnPlayAgain, btnBackToMenu, btnQuit);

	AddSprite(endPanelp1);
	AddSprite(endPanelp2);

	AddButton(btnPlayAgain);
	AddButton(btnBackToMenu);
	AddButton(btnQuit);

#ifndef _DEBUG
	Mix_PlayMusic(m_backgroundMusic, -1);
#endif
}

SDLSceneGame::~SDLSceneGame()
{
	Mix_FreeMusic(m_backgroundMusic);
}

void SDLSceneGame::InternalUpdate(float dt)
{
	m_markerViewMover->Update(dt);
	m_eliminatorViewController->Update(dt);
}

void SDLSceneGame::InternalRender(SDL_Renderer& renderer)
{
	
}

void SDLSceneGame::InternalOnMousePressed(Uint8 button)
{
	m_markerViewMover->MouseButtonPressed(button);
	m_eliminatorViewController->MouseButtonPressed(button);
}

void SDLSceneGame::InternalOnMouseReleased(Uint8 button)
{
	m_markerViewMover->MouseButtonReleased(button);
	m_eliminatorViewController->MouseButtonReleased(button);
}

bool SDLSceneGame::OnTryMoveMarker(const SDLMarkerView& markerView, int pos)
{
	const Morris::MorrisMarkerPtr marker = markerView.GetMarker();

	const std::vector<Morris::MorrisMarkerPtr>& unplacedMarkers = m_game->GetUnplacedMarkers();
	if (std::count(unplacedMarkers.cbegin(), unplacedMarkers.cend(), marker) > 0)
	{
		return m_game->PlaceMarketAtPoint(pos, marker);
	}
	else
	{
		return m_game->MoveMarkerToPoint(pos, marker);
	}
}

bool SDLSceneGame::OnTryEliminateMarker(const Morris::MorrisMarkerPtr marker)
{
	return m_game->EliminateMarker(marker);
}

#include <iostream> // TODO: remove this

void SDLSceneGame::OnPlayerTurnChangedCallback(Morris::MorrisPlayer player)
{
	std::cout << "Player turn changed" << std::endl;
}

void SDLSceneGame::OnGamestateChangedCallback(Morris::MorrisGameState previousGamestate, Morris::MorrisGameState currentGameState)
{
	std::cout << "game state changed" << std::endl;

	if (previousGamestate == Morris::MorrisGameState::RemoveP1Marker || previousGamestate == Morris::MorrisGameState::RemoveP2Marker)
		m_eliminationPanel->Hide();

	if (currentGameState == Morris::MorrisGameState::RemoveP1Marker || currentGameState == Morris::MorrisGameState::RemoveP2Marker)
	{
		m_markerMode = MarkerViewMode::Eliminating;
		m_eliminationPanel->Show(m_game->GetCurrentPlayerTurn());
	}
	else if (currentGameState == Morris::MorrisGameState::Playing)
	{
		m_markerMode = MarkerViewMode::Grabbing;
	}
	else
	{
		m_markerMode = MarkerViewMode::None;
	}
}

void SDLSceneGame::OnPlayerWinCallback(Morris::MorrisPlayer winner)
{
	const char* playerName = (winner == Morris::MorrisPlayer::Player1) ? "1" : "2";
	std::cout << "game over: player " << playerName << " wins" << std::endl;

	m_endGamePanelView->Show(winner);
}

void SDLSceneGame::OnMarkerEliminatedCallback(const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker elimited" << std::endl;

	// find the target marker
	// move it outside of screen or to graveyard point
	for (std::shared_ptr<SDLMarkerView>& markerView : m_markerViews)
	{
		if (markerView->GetMarker() == marker)
		{
			markerView->MoveToPosition(1300, 400);
		}
	}
}

void SDLSceneGame::OnMarkerPlacedCallback(int pos, const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker placed" << std::endl;
}

void SDLSceneGame::OnMarkerMovedCallback(int pos, const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker moved" << std::endl;
}

void SDLSceneGame::OnPlayAgainClick()
{
	SwitchScene("GameScene");
}

void SDLSceneGame::OnBackToMenuClick()
{
	SwitchScene("MainMenu");
}

void SDLSceneGame::OnQuitClick()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;

	SDL_PushEvent(&quitEvent);
}
