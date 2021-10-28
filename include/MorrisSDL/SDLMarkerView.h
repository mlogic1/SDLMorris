#pragma once

#include "SDLSprite.h"
#include <string>
#include "MorrisGame/MorrisMarker.h"

class SDLMarkerView : public SDLSprite
{
	public:
		SDLMarkerView(const std::string& textureName, SDL_Rect posAndSize, Morris::MorrisMarkerPtr marker);
		~SDLMarkerView();

		bool CanBeGrabbed() const;
		const Morris::MorrisMarkerPtr& GetMarker() const;

	private:
		Morris::MorrisMarkerPtr m_markerPtr;
};