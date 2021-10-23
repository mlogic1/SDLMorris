#include "MorrisGame/MorrisField.h"
#include <cmath>

namespace Morris
{
	MorrisField::MorrisField()
	{

	}

	const std::array<MorrisMarkerPtr, 24>& MorrisField::GetField() const
	{
		return _cells;
	}

	bool MorrisField::GetMarkerPosition(int& pos, const MorrisMarkerPtr marker) const
	{
		for (int i = 0; i < _cells.size(); ++i)
		{
			if (_cells[i] == marker)
			{
				pos = i;
				return true;
			}
		}
		return false;
	}

	const MorrisMarkerPtr MorrisField::GetAt(int pos) const
	{
		return _cells[pos];
	}
	
	bool MorrisField::SetAt(int pos, const MorrisMarkerPtr marker)
	{
		if (_cells[pos] != nullptr)
			return false;

		_cells[pos] = marker;
		return true;
	}

	bool MorrisField::SlideMarkerTo(int pos, const MorrisMarkerPtr marker)
	{
		int cpos;	// current marker spot
		if (!GetMarkerPosition(cpos, marker))
			return false;

		// check if target spot is free
		if (_cells[pos] != nullptr)
			return false;

		if (!AreAdjacent(cpos, pos))
			return false;

		// move and clear the previous spot
		_cells[pos] = std::move(_cells[cpos]);
		return true;
	}
	
	bool MorrisField::JumpMarkerTo(int pos, const MorrisMarkerPtr marker)
	{
		// jumps can only be made if that player has exactly 3 markers
		if (GetMarkerCount(marker->GetColor()) != 3)
			return false;
	
		// check if target spot is free
		if (_cells[pos] != nullptr)
			return false;

		int cpos;
		if (!GetMarkerPosition(cpos, marker))
			return false;

		if (_cells[pos] != nullptr)
			return false;
		
		// move and clear the previous spot
		_cells[pos] = std::move(_cells[cpos]);
		return true;
	}

	bool MorrisField::EliminateMarker(const MorrisMarkerPtr marker)
	{
		int pos;
		if (!GetMarkerPosition(pos, marker))
			return false;
		
		_cells[pos] = nullptr;
		return true;
	}

	int MorrisField::GetMarkerCount(MorrisPlayer player) const
	{
		int count = 0;

		for (const MorrisMarkerPtr marker : _cells)
		{
			if (marker->GetColor() == player)
				++count;
		}
		return count;
	}
	
	bool MorrisField::AreAdjacent(int pos1, int pos2) const
	{
		return _adjacents[pos1].find(pos2) != _adjacents[pos1].end();
	}
}