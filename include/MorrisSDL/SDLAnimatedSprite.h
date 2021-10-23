#pragma once

#include "SDLSprite.h"

class SDLAnimatedSprite : public SDLSprite
{
	public:
		SDLAnimatedSprite(const std::string& textureFile, SDL_Rect posAndSize, int textureWidth, int textureHeight, float frameTime, int frameCount, int frameWidth, int frameHeight);
		~SDLAnimatedSprite();

		void Update(float dt) override;
		void Render(SDL_Renderer& renderer) override;

	private:
		const int m_textureWidth;
		const int m_textureHeight;
		const float m_frameTime;
		const int m_frameCount;
		const int m_frameWidth;
		const int m_frameHeight;
		
		int m_currentFrame = 0;
		float m_currentFrametime = .0f;

		SDL_Rect m_srcRect = { 0, 0, m_frameWidth, m_frameHeight };
};

