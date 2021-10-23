#include "MorrisSDL/SDLWindow.h"
#include "MorrisSDL/SDLSceneMainMenu.h"
#include "MorrisSDL/SDLTextureLoader.h"
#include <string>

SDLWindow::SDLWindow()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	if (m_window == nullptr || m_renderer == nullptr)
	{
		throw std::string("Unable to init SDL");
	}

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
	{
		const char* err = IMG_GetError();
		throw std::string("Unable to init SDL IMG: " + std::string(err));
	}

	SDLTextureLoader::GetInstance().SetReferences(m_window, m_renderer);
	m_currentScene = std::make_unique<SDLSceneMainMenu>();	
}

SDLWindow::~SDLWindow()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

bool SDLWindow::IsRunning() const
{
	return m_isRunning;
}

void SDLWindow::Update()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	HandleInput(event);

	// delta
	int thisTime = SDL_GetTicks();
	float dt = ((float)thisTime - lastTime) / 1000.0f;
	lastTime = thisTime;
	m_currentScene->Update(dt);

	// render
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(m_renderer);
	//SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	m_currentScene->Render(*m_renderer);

	SDL_RenderPresent(m_renderer);
}

void SDLWindow::HandleInput(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_isRunning = false;
			}
			break;
		}

		case SDL_QUIT:
		{
			m_isRunning = false;
			break;
		}

		default:
		{
			break;
		}
	}
}
