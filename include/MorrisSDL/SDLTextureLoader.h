#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class SDLTextureLoader
{
public:
	static SDLTextureLoader& GetInstance()
	{
		static SDLTextureLoader instance;
		return instance;
	}

	SDL_Texture* LoadImage(const std::string& fileName)
	{
		static const std::string dataFolderName = "../data/";
		const std::string filePath = dataFolderName + fileName;

		SDL_Surface* surface = IMG_Load(filePath.c_str());

		if (!surface)
		{
			throw std::string("Unable to load file: " + fileName);
		}

		// SDL_Surface* optimizedSurface = SDL_ConvertSurface(surface, SDL_GetWindowSurface(MAIN_WINDOW)->format, 0);

		SDL_Texture* tx = SDL_CreateTextureFromSurface(MAIN_RENDERER, surface);
		SDL_FreeSurface(surface);
		// SDL_FreeSurface(optimizedSurface);
		return tx;
	}

private:
	SDLTextureLoader() {}

	SDLTextureLoader(const SDLTextureLoader& other) = delete;
	void operator=(const SDLTextureLoader& other) = delete;
	
private:
	void SetReferences(SDL_Window* window, SDL_Renderer* renderer)
	{
		MAIN_WINDOW = window;
		MAIN_RENDERER = renderer;
	}

private:
	static SDL_Window* MAIN_WINDOW;
	static SDL_Renderer* MAIN_RENDERER;

	friend class SDLWindow;
};