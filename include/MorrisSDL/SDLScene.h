#pragma once

#include "ISDLSprite.h"
#include "SDLSprite.h"
#include "SDLButton.h"
#include <SDL.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class SDLWindow;

class SDLScene
{
	public:
		SDLScene(SDLWindow& window);
		virtual ~SDLScene() = 0;

		void Update(float dt);
		void Render(SDL_Renderer& renderer);

		virtual void OnKeyPressed(SDL_Keycode key);
		virtual void OnKeyReleased(SDL_Keycode key);
		virtual void OnMousePressed(Uint8 button);
		virtual void OnMouseReleased(Uint8 button);

	protected:
		void AddSprite(std::shared_ptr<ISDLSprite> ptr);
		void AddButton(std::shared_ptr<SDLButton> ptr);

		void SwitchScene(const std::string& sceneName);

	protected:
		virtual void InternalUpdate(float dt);
		virtual void InternalRender(SDL_Renderer& renderer);
		
		virtual void InternalOnKeyPressed(SDL_Keycode key);
		virtual void InternalOnKeyReleased(SDL_Keycode key);
		virtual void InternalOnMousePressed(Uint8 button);
		virtual void InternalOnMouseReleased(Uint8 button);

	private:
		std::vector<std::shared_ptr<ISDLSprite>> m_sprites;
		std::vector<std::shared_ptr<SDLButton>> m_buttons;

		// scene switching - this should be handled by a scene switcher class
		SDLWindow& m_windowRef;
		std::shared_ptr<SDLSprite> transitionBox;
		Uint8 m_transitionBoxTargetAlpha = 0;
		void LerpTransitionBox(Uint8 target);
		std::string m_nextSceneName = "";
		bool m_isSwitchingScene = false;

		float m_transitionCounter = 0.0f;
		float m_transitionDuration = 0.750f;
};