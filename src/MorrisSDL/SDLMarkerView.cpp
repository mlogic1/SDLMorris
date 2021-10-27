#include "MorrisSDL/SDLMarkerView.h"


SDLMarkerView::SDLMarkerView(const std::string& textureName, SDL_Rect posAndSize, Morris::MorrisMarkerPtr marker) :
	SDLSprite(textureName, posAndSize)
{

}

SDLMarkerView::~SDLMarkerView()
{

}
