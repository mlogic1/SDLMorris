#pragma once

#include "MorrisField.h"
#include "MorrisGameState.h"
#include "MorrisPlayerTurn.h"

namespace Morris
{
	class MorrisGame
	{
	public:
		MorrisGame();
		~MorrisGame() = default;
		void ResetGame();

		MorrisGameState GetGameState() const;
		MorrisPlayerTurn GetCurrentPlayerTurn() const;

	private:
		MorrisField _gameField;
		MorrisGameState _gameState = MorrisGameState::Playing;
		MorrisPlayerTurn _currentPlayerTurn = MorrisPlayerTurn::Player1;
	};
}