#include "MorrisGame/MorrisGame.h"

namespace Morris
{
	MorrisGame::MorrisGame()
	{
		ResetGame();
	}

	void MorrisGame::ResetGame()
	{
		_gameField = MorrisField();
		_gameState = MorrisGameState::Playing;
		_currentPlayerTurn = MorrisPlayerTurn::Player1;
	}

	MorrisGameState MorrisGame::GetGameState() const
	{
		return _gameState;
	}
	MorrisPlayerTurn MorrisGame::GetCurrentPlayerTurn() const
	{
		return _currentPlayerTurn;
	}
}