#pragma once

#include "SDLSprite.h"
#include "MorrisGame/MorrisGame.h"
#include "SDLMarkerViewMode.h"
#include <SDL_mixer.h>
#include <functional>
#include <memory>
#include <vector>

class SDLMarkerViewEliminatorController
{
	public:
		SDLMarkerViewEliminatorController(std::shared_ptr<SDLSprite>& eliminatorSprite, const Morris::MorrisGame& game, const MarkerViewMode& viewMode, std::function<bool(const Morris::MorrisMarkerPtr)> tryEliminateCallback);
		~SDLMarkerViewEliminatorController();

		void Update(float dt);

		void MouseButtonPressed(Uint8 button);
		void MouseButtonReleased(Uint8 button);

	private:
		void OnHoverHitbox(int hitboxIndex);
		void OnLeaveHitbox();

	private:
		int m_currentlyHoveringHitboxIndex = -1;

		const std::vector<SDL_Rect> m_fieldPosHitboxes =
		{
			{281, 39, 85, 85},	// 0
			{597, 39, 85, 85},	// 1
			{916, 39, 85, 85},	// 2
			{383, 145, 85, 85},	// 3
			{598, 145, 85, 85},	// 4
			{808, 145, 85, 85},	// 5
			{493, 250, 85, 85},	// 6
			{598, 250, 85, 85},	// 7
			{705, 250, 85, 85},	// 8
			{278, 356, 85, 85},	// 9
			{384, 356, 85, 85},	// 10
			{492, 356, 85, 85},	// 11
			{705, 356, 85, 85},	// 12
			{809, 356, 85, 85},	// 13
			{916, 356, 85, 85},	// 14
			{489, 463, 85, 85},	// 15
			{600, 463, 85, 85},	// 16
			{708, 463, 85, 85},	// 17
			{383, 570, 85, 85},	// 18
			{598, 570, 85, 85},	// 19
			{808, 570, 85, 85},	// 20
			{281, 675, 85, 85},	// 21
			{597, 675, 85, 85},	// 22
			{916, 675, 85, 85}	// 23
		};

		std::function<bool(const Morris::MorrisMarkerPtr)> m_tryEliminateCallback;
		const Morris::MorrisGame& m_gameRef;
		const MarkerViewMode& m_currentViewModeRef;
		std::shared_ptr<SDLSprite> m_eliminatorSprite = nullptr;

		// audio
		Mix_Chunk* m_eliminatorConfirmSound = nullptr;
		Mix_Chunk* m_eliminatorHoverSound = nullptr;
};