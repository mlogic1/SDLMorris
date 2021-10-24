#include "MorrisSDL/SDLScene.h"

SDLScene::SDLScene()
{

}

SDLScene::~SDLScene()
{
	m_sprites.clear();
	m_buttons.clear();
}

void SDLScene::Update(float dt)
{
	for (std::unique_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Update(dt);

	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);

	for (std::unique_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->Update(dt, cursorX, cursorY);

	InternalUpdate(dt);
}

void SDLScene::Render(SDL_Renderer& renderer)
{
	for (std::unique_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Render(renderer);

	for (std::unique_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->Render(renderer);

	InternalRender(renderer);
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
	for (std::unique_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->OnMousePressed(button);

	InternalOnMousePressed(button);
}

void SDLScene::OnMouseReleased(Uint8 button)
{
	for (std::unique_ptr<SDLButton>& buttonPtr : m_buttons)
		buttonPtr->OnMouseReleased(button);

	InternalOnMouseReleased(button);
}

void SDLScene::AddSprite(std::unique_ptr<ISDLSprite> ptr)
{
	m_sprites.emplace_back(std::move(ptr));
}

void SDLScene::AddButton(std::unique_ptr<SDLButton> ptr)
{
	m_buttons.emplace_back(std::move(ptr));
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
