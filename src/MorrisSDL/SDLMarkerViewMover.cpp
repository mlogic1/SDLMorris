#include "MorrisSDL/SDLMarkerViewMover.h"

SDLMarkerViewMover::SDLMarkerViewMover(const std::vector<std::shared_ptr<SDLMarkerView>>& markerViews) :
	m_markerViews(markerViews)
{

}

SDLMarkerViewMover::~SDLMarkerViewMover()
{

}

void SDLMarkerViewMover::Update(float dt)
{
	if (m_currentlyHeldMarker)
	{
		int cursorX, cursorY;
		SDL_GetMouseState(&cursorX, &cursorY);
		m_currentlyHeldMarker->SetPosition(cursorX - 42, cursorY - 42);


		m_currentlyHoveringHitboxIndex = -1;
		for (int i = 0; i < m_fieldPosHitboxes.size(); ++i)
		{
			const SDL_Rect& hitBox = m_fieldPosHitboxes[i];
			if (cursorX >= hitBox.x && cursorX <= hitBox.x + hitBox.w && cursorY >= hitBox.y && cursorY <= hitBox.y + hitBox.h)
			{
				m_currentlyHoveringHitboxIndex = i;
			}
		}		
	}
}

void SDLMarkerViewMover::MouseButtonPressed(Uint8 button)
{
	if (button != SDL_BUTTON_LEFT)
		return;

	if (m_currentlyHeldMarker)
		return;

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	for (const std::shared_ptr<SDLMarkerView>& markerView : m_markerViews)
	{
		const SDL_Rect& markerRect = markerView->GetRect();
		if (cursorX >= markerRect.x && cursorX <= markerRect.x + markerRect.w && cursorY >= markerRect.y && cursorY <= markerRect.y + markerRect.h)
		{
			m_currentlyHeldMarker = markerView;
			break;
		}
	}
}

void SDLMarkerViewMover::MouseButtonReleased(Uint8 button)
{
	if (button != SDL_BUTTON_LEFT)
		return;

	if (!m_currentlyHeldMarker)
		return;

	if (m_currentlyHoveringHitboxIndex == -1)
	{
		
	}
	else
	{
		
	}

	m_currentlyHoveringHitboxIndex = -1;
	m_currentlyHeldMarker = nullptr;
}
