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

	m_game = std::make_unique<Morris::MorrisGame>();

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
		AddSprite(markerView);
		m_markerViews.emplace_back(std::move(markerView));
	}
	m_markerViewMover = std::make_unique<SDLMarkerViewMover>(m_markerViews);

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
#include <iostream>
void SDLSceneGame::InternalOnMousePressed(Uint8 button)
{
	m_markerViewMover->MouseButtonPressed(button);
}

void SDLSceneGame::InternalOnMouseReleased(Uint8 button)
{
	m_markerViewMover->MouseButtonReleased(button);

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	std::cout << "X: " << cursorX - 42 << " " << "Y: " << cursorY - 42 << std::endl;
}