#include "SDLMarkerViewEliminatorController.h"
#include "SDLAudioLoader.h"

SDLMarkerViewEliminatorController::SDLMarkerViewEliminatorController(std::shared_ptr<SDLSprite>& eliminatorSprite, const Morris::MorrisGame& game, const MarkerViewMode& viewMode, std::function<bool(const Morris::MorrisMarkerPtr)> tryEliminateCallback) :
	m_eliminatorSprite(eliminatorSprite),
	m_gameRef(game),
	m_currentViewModeRef(viewMode),
	m_tryEliminateCallback(tryEliminateCallback)
{
	// m_eliminatorConfirmSound = SDLAudioLoader::GetInstance().LoadChunk("");
	m_eliminatorHoverSound = SDLAudioLoader::GetInstance().LoadChunk("eliminator_hover.ogg");
}

SDLMarkerViewEliminatorController::~SDLMarkerViewEliminatorController()
{
	Mix_FreeChunk(m_eliminatorConfirmSound);
	Mix_FreeChunk(m_eliminatorHoverSound);
}

void SDLMarkerViewEliminatorController::Update(float dt)
{
	if (m_currentViewModeRef != MarkerViewMode::Eliminating)
		return;
	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	
	bool isInHitbox = false;
	for (int i = 0; i < m_fieldPosHitboxes.size(); ++i)
	{
		const SDL_Rect& hitBox = m_fieldPosHitboxes[i];
		if (cursorX >= hitBox.x && cursorX <= hitBox.x + hitBox.w && cursorY >= hitBox.y && cursorY <= hitBox.y + hitBox.h)
		{
			isInHitbox = true;
			if (m_currentlyHoveringHitboxIndex != i)
			{
				const Morris::MorrisMarkerPtr marker = m_gameRef.GetMarkerAt(i);
				if (marker && marker->GetColor() != m_gameRef.GetCurrentPlayerTurn() && m_gameRef.CanMarkerBeEliminated(marker))
					OnHoverHitbox(i);
			}
		}
	}

	if (!isInHitbox && m_currentlyHoveringHitboxIndex != -1)
	{
		OnLeaveHitbox();
	}
}

void SDLMarkerViewEliminatorController::MouseButtonPressed(Uint8 button)
{

}

void SDLMarkerViewEliminatorController::MouseButtonReleased(Uint8 button)
{
	if (m_currentViewModeRef != MarkerViewMode::Eliminating)
		return;
	
	if (button != SDL_BUTTON_LEFT)
		return;
	
	if (m_currentlyHoveringHitboxIndex != -1)
	{
		const Morris::MorrisMarkerPtr marker = m_gameRef.GetMarkerAt(m_currentlyHoveringHitboxIndex);
		if (marker)
		{
			m_tryEliminateCallback(marker);
			OnLeaveHitbox();
		}
	}
}

void SDLMarkerViewEliminatorController::OnHoverHitbox(int hitboxIndex)
{
	m_currentlyHoveringHitboxIndex = hitboxIndex;
	m_eliminatorSprite->SetRect(m_fieldPosHitboxes[hitboxIndex]);
	m_eliminatorSprite->SetAlpha(255);
	Mix_PlayChannel(-1, m_eliminatorHoverSound, 0);
}

void SDLMarkerViewEliminatorController::OnLeaveHitbox()
{
	m_currentlyHoveringHitboxIndex = -1;
	m_eliminatorSprite->SetAlpha(0);
	// Mix_PlayChannel(-1, m_eliminatorHoverSound, 0);
}
