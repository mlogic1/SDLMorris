#pragma once

#include <SDL_image.h>
#include <functional>
#include <string>

class SDLButton
{
	private:
		enum class SDLButtonState
		{
			IDLE = 0,
			PRESSED,
			HOVER
		};

	public:
		SDLButton(SDL_Rect posAndSize, const std::string& textureIdle, const std::string& textureHover, const std::string& texturePressed, std::function<void()> pressedCallback);
		~SDLButton();

		void Update(float dt, int cursorX, int cursorY);
		void Render(SDL_Renderer& renderer);

		void OnMousePressed(Uint8 button);
		void OnMouseReleased(Uint8 button);

	private:
		bool IsCursorInBounds(int cursorX, int cursorY) const;

	private:
		SDLButtonState m_currentState = SDLButtonState::IDLE;
		SDL_Texture* m_textureIdle = nullptr;
		SDL_Texture* m_textureHover = nullptr;
		SDL_Texture* m_texturePressed = nullptr;

		SDL_Texture* m_currentTexture = nullptr;

		SDL_Rect m_posSize;

		std::function<void()> m_callback;
};

