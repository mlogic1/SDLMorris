#include "MorrisSDL/SDLSceneGame.h"
#include "MorrisSDL/SDLTextureLoader.h"
#include "MorrisSDL/SDLAudioLoader.h"

SDLSceneGame::SDLSceneGame(SDLWindow& window) :
	SDLScene(window)
{
	SDL_Rect rectBG = {0, 0, 1280, 800};
	SDL_Rect boardRect = { 290, 50, 700, 700 };
	
	AddSprite(std::make_unique<SDLSprite>("menu.png", rectBG));
	AddSprite(std::make_unique<SDLSprite>("board.png", boardRect));

	m_backgroundMusic = SDLAudioLoader::GetInstance().LoadMusic("menubgm.ogg");

	m_game = std::make_unique<Morris::MorrisGame>(
		std::bind(&SDLSceneGame::OnPlayerTurnChanged, this, std::placeholders::_1),
		std::bind(&SDLSceneGame::OnGameStateChanged, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&SDLSceneGame::OnPlayerWin, this, std::placeholders::_1),
		std::bind(&SDLSceneGame::OnMarkerEliminated, this, std::placeholders::_1),
		std::bind(&SDLSceneGame::OnMarkerPlaced, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&SDLSceneGame::OnMarkerMoved, this, std::placeholders::_1, std::placeholders::_2)
		);

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
	// if (m_markerMode == MarkerMode::Grabbing)
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

#include <iostream>
void SDLSceneGame::OnPlayerTurnChanged(Morris::MorrisPlayer player)
{
	std::cout << "Player turn changed" << std::endl;
}

void SDLSceneGame::OnGameStateChanged(Morris::MorrisGameState previousState, Morris::MorrisGameState newState)
{
	std::cout << "game state changed" << std::endl;
	
	if (previousState == Morris::MorrisGameState::RemoveP1Marker || previousState == Morris::MorrisGameState::RemoveP2Marker)
		m_eliminationPanel->Hide();

	if (newState == Morris::MorrisGameState::RemoveP1Marker || newState == Morris::MorrisGameState::RemoveP2Marker)
	{
		m_markerMode = MarkerViewMode::Eliminating;
		m_eliminationPanel->Show(m_game->GetCurrentPlayerTurn());
	}
	else if (newState == Morris::MorrisGameState::Playing)
	{
		m_markerMode = MarkerViewMode::Grabbing;
	}
	else
	{
		m_markerMode = MarkerViewMode::None;
	}
}

void SDLSceneGame::OnPlayerWin(Morris::MorrisPlayer winningPlayer)
{
	const char* playerName = (winningPlayer == Morris::MorrisPlayer::Player1) ? "1" : "2";
	std::cout << "game over: player " << playerName << " wins" << std::endl;
}

void SDLSceneGame::OnMarkerEliminated(const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker elimited" << std::endl;
}

void SDLSceneGame::OnMarkerPlaced(int pos, const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker placed" << std::endl;
}

void SDLSceneGame::OnMarkerMoved(int pos, const Morris::MorrisMarkerPtr marker)
{
	std::cout << "marker moved" << std::endl;
}
