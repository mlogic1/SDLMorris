#include "MorrisSDL/SDLSceneMainMenu.h"
#include "MorrisSDL/SDLTextureLoader.h"
#include "MorrisSDL/SDLAnimatedSprite.h"
#include "MorrisSDL/SDLAudioLoader.h"
#include "MorrisSDL/SDLSprite.h"

SDLSceneMainMenu::SDLSceneMainMenu(SDLWindow& window) :
	SDLScene(window)
{
	SDL_Rect rectBG = {0, 0, 1280, 800};
	SDL_Rect windmillRect = { 1000, 625, 192, 192 };
	SDL_Rect titleRect = { 313, -10, 655, 225 };
	SDL_Rect containerRect = { 40, 255, 473, 496 };	// 404 for center

	SDL_Rect playBtnRect = { 125, 350, 304, 85 };
	SDL_Rect quitBtnRect = { 125, 550, 304, 85 };

	SDL_Rect transitionBoxRect = { 0, 0, 1280, 800 };
	
	AddSprite(std::make_unique<SDLSprite>("menu.png", rectBG));
	AddSprite(std::make_unique<SDLSprite>("title.png", titleRect));
	AddSprite(std::make_unique<SDLSprite>("container_buttons.png", containerRect));
	AddSprite(std::make_unique<SDLAnimatedSprite>("windmill.png", windmillRect, 1024, 128, 0.16f, 8, 128, 128));
	AddButton(std::make_unique<SDLButton>(playBtnRect, "play_idle.png", "play_hover.png", "play_pressed.png", std::bind(&SDLSceneMainMenu::OnPlayButtonPressed, this), "hover.ogg", "start_game.ogg"));
	AddButton(std::make_unique<SDLButton>(quitBtnRect, "quit_idle.png", "quit_hover.png", "quit_pressed.png", std::bind(&SDLSceneMainMenu::OnQuitButtonPressed, this), "hover.ogg", "start_game.ogg"));

	m_backgroundMusic = SDLAudioLoader::GetInstance().LoadMusic("menubgm.ogg");
#ifndef _DEBUG
	Mix_PlayMusic(m_backgroundMusic, -1);
#endif
}

SDLSceneMainMenu::~SDLSceneMainMenu()
{
	Mix_FreeMusic(m_backgroundMusic);
}

void SDLSceneMainMenu::InternalUpdate(float dt)
{

}

void SDLSceneMainMenu::InternalRender(SDL_Renderer& renderer)
{
	
}

void SDLSceneMainMenu::OnPlayButtonPressed()
{
	SwitchScene("MainMenu");
}

void SDLSceneMainMenu::OnQuitButtonPressed()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;

	SDL_PushEvent(&quitEvent);
}
