#include "SDLMarkerViewMover.h"
#include "SDLAudioLoader.h"

SDLMarkerViewMover::SDLMarkerViewMover(const std::vector<std::shared_ptr<SDLMarkerView>>& markerViews, const MarkerViewMode& viewMode, std::function<bool(const SDLMarkerView&, int)> tryMoveCallback) :
	m_markerViews(markerViews),
	m_currentViewModeRef(viewMode),
	m_tryMoveCallback(tryMoveCallback)
{
	for (const SDL_Rect& hitboxRect : m_fieldPosHitboxes)
	{
		m_hitBoxes.emplace_back(std::make_shared<SDLSprite>("hitbox_green.png", hitboxRect));
	}	

	m_successfulMoveSound = SDLAudioLoader::GetInstance().LoadChunk("action_success.ogg");
	m_failedMoveSound = SDLAudioLoader::GetInstance().LoadChunk("action_fail.ogg");
}

SDLMarkerViewMover::~SDLMarkerViewMover()
{
	Mix_FreeChunk(m_successfulMoveSound);
	Mix_FreeChunk(m_failedMoveSound);
}

void SDLMarkerViewMover::Update(float dt)
{
	if (m_currentlyHeldMarker)
	{
		int cursorX, cursorY;
		SDL_GetMouseState(&cursorX, &cursorY);
		m_currentlyHeldMarker->SetPosition(cursorX - 42, cursorY - 42);


		m_currentlyHoveringHitboxIndex = -1;
		if (m_currentViewModeRef != MarkerViewMode::Grabbing)
			return;
		for (int i = 0; i < m_fieldPosHitboxes.size(); ++i)
		{
			const SDL_Rect& hitBox = m_fieldPosHitboxes[i];
			if (cursorX >= hitBox.x && cursorX <= hitBox.x + hitBox.w && cursorY >= hitBox.y && cursorY <= hitBox.y + hitBox.h)
			{
				m_currentlyHoveringHitboxIndex = i;
				m_hitBoxes[i]->SetAlpha(255);
			}
			else
			{
				m_hitBoxes[i]->SetAlpha(0);
			}
		}
	}
	else
	{
		for (auto hitbox : m_hitBoxes)
		{
			hitbox->SetAlpha(0);
		}
	}
}

void SDLMarkerViewMover::MouseButtonPressed(Uint8 button)
{
	if (m_currentViewModeRef != MarkerViewMode::Grabbing)
		return;

	if (button != SDL_BUTTON_LEFT)
		return;

	if (m_currentlyHeldMarker)
		return;

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	for (const std::shared_ptr<SDLMarkerView>& markerView : m_markerViews)
	{
		if (!markerView->CanBeGrabbed())
			continue;
		const SDL_Rect& markerRect = markerView->GetRect();
		if (cursorX >= markerRect.x && cursorX <= markerRect.x + markerRect.w && cursorY >= markerRect.y && cursorY <= markerRect.y + markerRect.h)
		{
			m_currentlyHeldMarker = markerView;
			m_grabbedMarkerRect = markerView->GetRect();
			break;
		}
	}
}

void SDLMarkerViewMover::MouseButtonReleased(Uint8 button)
{
	if (m_currentViewModeRef != MarkerViewMode::Grabbing)
		return;

	if (button != SDL_BUTTON_LEFT)
		return;

	if (!m_currentlyHeldMarker)
		return;

	if (m_currentlyHoveringHitboxIndex == -1)
	{
		m_currentlyHeldMarker->MoveToPosition(m_grabbedMarkerRect.x, m_grabbedMarkerRect.y);
		Mix_PlayChannel(-1, m_failedMoveSound, 0);
	}
	else
	{
		if (m_tryMoveCallback(*m_currentlyHeldMarker, m_currentlyHoveringHitboxIndex))
		{
			m_currentlyHeldMarker->SetRect(m_hitBoxes[m_currentlyHoveringHitboxIndex]->GetRect());
			Mix_PlayChannel(-1, m_successfulMoveSound, 0);
		}
		else
		{
			m_currentlyHeldMarker->MoveToPosition(m_grabbedMarkerRect.x, m_grabbedMarkerRect.y);
			Mix_PlayChannel(-1, m_failedMoveSound, 0);
		}
	}

	m_currentlyHoveringHitboxIndex = -1;
	m_currentlyHeldMarker = nullptr;
}

const std::vector<std::shared_ptr<SDLSprite>>& SDLMarkerViewMover::GetHitboxes() const
{
	return m_hitBoxes;
}
