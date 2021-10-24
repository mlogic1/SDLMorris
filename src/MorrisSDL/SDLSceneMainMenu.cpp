#include "MorrisSDL/SDLSceneMainMenu.h"
#include "MorrisSDL/SDLTextureLoader.h"
#include "MorrisSDL/SDLSprite.h"
#include "MorrisSDL/SDLAnimatedSprite.h"
#include "MorrisSDL/SDLAudioLoader.h"
#include <memory>

SDLSceneMainMenu::SDLSceneMainMenu()
{
	SDL_Rect rectBG = {0, 0, 1280, 800};
	SDL_Rect windmillRect = { 1000, 625, 192, 192 };
	SDL_Rect titleRect = { 313, -10, 655, 225 };
	SDL_Rect containerRect = { 404, 255, 473, 496 };
	
	AddSprite(std::make_unique<SDLSprite>("menu.png", rectBG));
	AddSprite(std::make_unique<SDLSprite>("title.png", titleRect));
	AddSprite(std::make_unique<SDLSprite>("container_buttons.png", containerRect));
	AddSprite(std::make_unique<SDLAnimatedSprite>("windmill.png", windmillRect, 1024, 128, 0.036f, 8, 128, 128));

	m_backgroundMusic = SDLAudioLoader::GetInstance().LoadMusic("menubgm.ogg");
	Mix_PlayMusic(m_backgroundMusic, -1);
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
