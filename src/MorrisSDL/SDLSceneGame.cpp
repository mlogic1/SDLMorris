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

	m_markerViewMover = std::make_unique<SDLMarkerViewMover>(m_markerViews, std::bind(&SDLSceneGame::OnTryMoveMarker, this, std::placeholders::_1, std::placeholders::_2));
	
	for (auto hitbox : m_markerViewMover->GetHitboxes())
	{
		AddSprite(hitbox);
		hitbox->SetAlpha(0);
	}

	for (auto markerView : m_markerViews)
	{
		AddSprite(markerView);
	}

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
}

void SDLSceneGame::InternalRender(SDL_Renderer& renderer)
{
	
}

void SDLSceneGame::InternalOnMousePressed(Uint8 button)
{
	m_markerViewMover->MouseButtonPressed(button);
}

void SDLSceneGame::InternalOnMouseReleased(Uint8 button)
{
	m_markerViewMover->MouseButtonReleased(button);

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
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

#include <iostream>
void SDLSceneGame::OnPlayerTurnChanged(Morris::MorrisPlayer player)
{
	std::cout << "Player turn changed" << std::endl;
}

void SDLSceneGame::OnGameStateChanged(Morris::MorrisGameState previousState, Morris::MorrisGameState newState)
{
	std::cout << "game state changed" << std::endl;
	// TODO switch between grabbing and eliminating mode for markers
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
