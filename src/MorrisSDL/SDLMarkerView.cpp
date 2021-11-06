#include "SDLMarkerView.h"


SDLMarkerView::SDLMarkerView(const std::string& textureName, SDL_Rect posAndSize, Morris::MorrisMarkerPtr marker) :
	SDLSprite(textureName, posAndSize),
	m_markerPtr(marker)
{
	
}

SDLMarkerView::~SDLMarkerView()
{

}

bool SDLMarkerView::CanBeGrabbed() const
{
	return !m_isMoving;
}

const Morris::MorrisMarkerPtr& SDLMarkerView::GetMarker() const
{
	return m_markerPtr;
}
