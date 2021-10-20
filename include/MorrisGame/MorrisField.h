#pragma once

#include "MorrisCell.h"
#include <array>

namespace Morris
{
	class MorrisField
	{
	private:
		MorrisField();

		const std::array<std::array<MorrisCell, 3>, 3>& GetField() const;

	private:
		std::array<std::array<MorrisCell, 3>, 3> _cells;

		friend class MorrisGame;
	};
}

