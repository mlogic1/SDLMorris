#include "MorrisSDL/SDLScene.h"
#include "MorrisSDL/SDLWindow.h"

SDLScene::SDLScene(SDLWindow& window) :
	m_windowRef(window)
{
	SDL_Rect transitionBoxRect = { 0,0, 1280, 800 };
	transitionBox = std::make_unique<SDLSprite>("black_block.jpg", transitionBoxRect);
}

SDLScene::~SDLScene()
{
	m_sprites.clear();
	m_buttons.clear();
}

void SDLScene::Update(float dt)
{
	for (std::shared_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Update(dt);

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);

	for (std::shared_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->Update(dt, cursorX, cursorY);

	InternalUpdate(dt);
	m_transitionCounter += dt;
	transitionBox->Update(dt);
	LerpTransitionBox(m_transitionBoxTargetAlpha);
	if (m_isSwitchingScene)
	{
		if (m_transitionCounter > m_transitionDuration)
		{
			m_isSwitchingScene = false;
			m_windowRef.SwitchScene(m_nextSceneName);
		}
	}

}

void SDLScene::Render(SDL_Renderer& renderer)
{
	for (std::shared_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Render(renderer);

	for (std::shared_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->Render(renderer);

	InternalRender(renderer);
	transitionBox->Render(renderer);
}

void SDLScene::OnKeyPressed(SDL_Keycode key)
{
	
	InternalOnKeyPressed(key);
}

void SDLScene::OnKeyReleased(SDL_Keycode key)
{
	
	InternalOnKeyReleased(key);
}

void SDLScene::OnMousePressed(Uint8 button)
{
	for (std::shared_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->OnMousePressed(button);

	InternalOnMousePressed(button);
}

void SDLScene::OnMouseReleased(Uint8 button)
{
	for (std::shared_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->OnMouseReleased(button);

	InternalOnMouseReleased(button);
}

void SDLScene::AddSprite(std::shared_ptr<ISDLSprite> ptr)
{
	m_sprites.emplace_back(std::move(ptr));
}

void SDLScene::AddButton(std::shared_ptr<SDLButton> ptr)
{
	m_buttons.emplace_back(std::move(ptr));
}

void SDLScene::SwitchScene(const std::string& sceneName)
{
	if ((sceneName != "MainMenu" && sceneName != "GameScene") || m_isSwitchingScene)
		return;

	m_isSwitchingScene = true;
	m_transitionCounter = 0.0f;
	m_transitionBoxTargetAlpha = 255;
	m_nextSceneName = sceneName;
}

void SDLScene::InternalUpdate(float dt)
{
	// To be overriden if needed
}

void SDLScene::InternalRender(SDL_Renderer& renderer)
{
	// To be overriden if needed
}

void SDLScene::InternalOnKeyPressed(SDL_Keycode key)
{
	// To be overriden if needed
}

void SDLScene::InternalOnKeyReleased(SDL_Keycode key)
{
	// To be overriden if needed
}

void SDLScene::InternalOnMousePressed(Uint8 button)
{
	// To be overriden if needed
}

void SDLScene::InternalOnMouseReleased(Uint8 button)
{
	// To be overriden if needed
}

void SDLScene::LerpTransitionBox(Uint8 target)
{	
	Uint8 current = ((SDLSprite*)(transitionBox.get()))->GetAlpha();
	current = current + (target - current) * (m_transitionCounter / m_transitionDuration);
	((SDLSprite*)(transitionBox.get()))->SetAlpha(current);
}
