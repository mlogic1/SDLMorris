#pragma once

#include "ISDLSprite.h"
#include "SDLButton.h"
#include <SDL.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class SDLScene
{
	public:
		SDLScene();
		virtual ~SDLScene() = 0;

		void Update(float dt);
		void Render(SDL_Renderer& renderer);

		virtual void OnKeyPressed(SDL_Keycode key);
		virtual void OnKeyReleased(SDL_Keycode key);
		virtual void OnMousePressed(Uint8 button);
		virtual void OnMouseReleased(Uint8 button);

	protected:
		void AddSprite(std::unique_ptr<ISDLSprite> ptr);
		void AddButton(std::unique_ptr<SDLButton> ptr);

	protected:
		virtual void InternalUpdate(float dt);
		virtual void InternalRender(SDL_Renderer& renderer);
		
		virtual void InternalOnKeyPressed(SDL_Keycode key);
		virtual void InternalOnKeyReleased(SDL_Keycode key);
		virtual void InternalOnMousePressed(Uint8 button);
		virtual void InternalOnMouseReleased(Uint8 button);

	private:
		std::vector<std::unique_ptr<ISDLSprite>> m_sprites;
		std::vector<std::unique_ptr<SDLButton>> m_buttons;
};

