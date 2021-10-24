#include "MorrisSDL/SDLButton.h"
#include "MorrisSDL/SDLTextureLoader.h"


SDLButton::SDLButton(SDL_Rect posAndSize, const std::string& textureIdle, const std::string& textureHover, const std::string& texturePressed, std::function<void()> pressedCallback) :
	m_posSize(posAndSize),
	m_callback(pressedCallback)
{
	m_textureIdle = SDLTextureLoader::GetInstance().LoadImage(textureIdle);
	m_textureHover = SDLTextureLoader::GetInstance().LoadImage(textureHover);
	m_texturePressed = SDLTextureLoader::GetInstance().LoadImage(texturePressed);
}

SDLButton::~SDLButton()
{
	SDL_DestroyTexture(m_textureIdle);
	SDL_DestroyTexture(m_textureHover);
	SDL_DestroyTexture(m_texturePressed);
}

void SDLButton::Update(float dt, int cursorX, int cursorY)
{
	if (IsCursorInBounds(cursorX, cursorY))
	{
		if (m_currentState == SDLButtonState::IDLE)
		{
			m_currentState = SDLButtonState::HOVER;
		}
	}
	else
	{
		if (m_currentState == SDLButtonState::HOVER)
		{
			m_currentState = SDLButtonState::IDLE;
		}
	}

	switch (m_currentState)
	{
		case SDLButtonState::IDLE:
			m_currentTexture = m_textureIdle;
			break;

		case SDLButtonState::HOVER:
			m_currentTexture = m_textureHover;
			break;

		case SDLButtonState::PRESSED:
			m_currentTexture = m_texturePressed;
			break;

		default:
			m_currentTexture = m_textureIdle;
			break;
	}
}

void SDLButton::Render(SDL_Renderer& renderer)
{
	SDL_RenderCopy(&renderer, m_currentTexture, NULL, &m_posSize);
}

void SDLButton::OnMousePressed(Uint8 button)
{
	if (m_currentState == SDLButtonState::HOVER)
	{
		m_currentState = SDLButtonState::PRESSED;
	}
}

void SDLButton::OnMouseReleased(Uint8 button)
{
	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	bool isInbounds = IsCursorInBounds(cursorX, cursorY);
	if (m_currentState == SDLButtonState::PRESSED && isInbounds)
	{
		m_currentState = SDLButtonState::HOVER;
		m_callback();
	}
	else
	{
		m_currentState = SDLButtonState::IDLE;
	}
}

bool SDLButton::IsCursorInBounds(int cursorX, int cursorY) const
{
	if (cursorX >= m_posSize.x && cursorX <= m_posSize.x + m_posSize.w && cursorY >= m_posSize.y && cursorY <= m_posSize.y + m_posSize.h)
		return true;
	return false;
}
