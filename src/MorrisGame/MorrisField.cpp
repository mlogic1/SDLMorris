#include "MorrisGame/MorrisField.h"

namespace Morris
{
	MorrisField::MorrisField()
	{

	}

	const std::array<std::array<MorrisCell, 3>, 3>& MorrisField::GetField() const
	{
		return _cells;
	}
}