#pragma once

#include <SDL.h>

class ISDLSprite
{
public:
	virtual ~ISDLSprite() = default;
	virtual void Update(float dt) {};
	virtual void Render(SDL_Renderer& renderer) = 0;
	virtual const SDL_Rect& GetRect() const = 0;
	virtual void SetPosition(int x, int y) = 0;
};

