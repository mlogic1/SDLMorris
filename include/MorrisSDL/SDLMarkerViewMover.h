#pragma once

#include "SDLMarkerView.h"
#include <SDL_mixer.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

/* TODO remove positioning markers from this class to game class callbacks, this class should
only move the markers when grabbing, not set their final position */

class SDLMarkerViewMover
{
	public:
		SDLMarkerViewMover(const std::vector<std::shared_ptr<SDLMarkerView>>& markerViews, std::function<bool(const SDLMarkerView&, int)> tryMoveCallback);
		~SDLMarkerViewMover();

		void Update(float dt);

		void MouseButtonPressed(Uint8 button);
		void MouseButtonReleased(Uint8 button);

		const std::vector<std::shared_ptr<SDLSprite>>& GetHitboxes() const;

	private:
		const std::vector<std::shared_ptr<SDLMarkerView>>& m_markerViews;
		std::shared_ptr<SDLMarkerView> m_currentlyHeldMarker = nullptr;

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

		std::function<bool(const SDLMarkerView&, int)> m_tryMoveCallback;
		std::vector<std::shared_ptr<SDLSprite>> m_hitBoxes;

		SDL_Rect m_grabbedMarkerRect = { 0, 0, 0, 0};

		// audio
		Mix_Chunk* m_successfulMoveSound = nullptr;
		Mix_Chunk* m_failedMoveSound = nullptr;
};