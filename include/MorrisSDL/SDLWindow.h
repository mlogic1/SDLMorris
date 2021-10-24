#pragma once

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

#include "SDLScene.h"
#include "SDLEvent.h"
#include <memory>
#include <string>

class SDLWindow
{
	public:
		SDLWindow();
		~SDLWindow();

		bool IsRunning() const;
		void Update();

	private:
		void HandleInput(const SDL_Event& event);

	private:
		// Field* m_field = nullptr;

		// scene system
		std::unique_ptr<SDLScene> m_currentScene;

		// SDL
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		static constexpr const char* WINDOW_NAME = "Mills: A Nine Men's Morris Game";
		static constexpr int WINDOW_WIDTH = 1280;
		static constexpr int WINDOW_HEIGHT = 800;

		bool m_isRunning = true;

		// delta time
		int lastTime = 0;
};