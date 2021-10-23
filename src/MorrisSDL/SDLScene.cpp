#include "MorrisSDL/SDLScene.h"

SDLScene::SDLScene()
{

}

SDLScene::~SDLScene()
{
	m_sprites.clear();
}

void SDLScene::Update(float dt)
{
	for (std::unique_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Update(dt);

	InternalUpdate(dt);
}

void SDLScene::Render(SDL_Renderer& renderer)
{
	for (std::unique_ptr<ISDLSprite>& spritePtr : m_sprites)
		spritePtr->Render(renderer);

	InternalRender(renderer);
}

void SDLScene::AddSprite(std::unique_ptr<ISDLSprite> ptr)
{
	m_sprites.emplace_back(std::move(ptr));
}

void SDLScene::InternalUpdate(float dt)
{
	// To be overriden if needed
}

void SDLScene::InternalRender(SDL_Renderer& renderer)
{
	// To be overriden if needed
}
