#pragma once

#include "ISDLSprite.h"
#include <SDL_image.h>
#include <string>

class SDLSprite : public ISDLSprite
{
	public:
		SDLSprite(const std::string& textureFile, SDL_Rect posAndSize);
		~SDLSprite();

		Uint8 GetAlpha() const;
		void SetAlpha(Uint8 value);
		virtual void Update(float dt) override;
		virtual void Render(SDL_Renderer& renderer) override;
		virtual const SDL_Rect& GetRect() const override;
		void SetRect(const SDL_Rect& rect) override;
		void SetPosition(int x, int y) override;
		void MoveToPosition(int x, int y);

	protected:
		SDL_Texture* m_texture = nullptr;
		SDL_Rect m_posSize;

		Uint8 m_alpha = 255;

		bool m_isMoving = false;
		int m_targetPosX, m_targetPosY;
		float m_movingTimer = 0.0f;
		const float m_movingDuration = 0.550f;

	private:
		void CancelMoving();
		inline constexpr int Lerp(int a, int b)
		{
			a = static_cast<int>(a + (b - a) * (m_movingTimer / m_movingDuration));
			return a;
		}

};

