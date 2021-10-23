#pragma once

#include "MorrisMarker.h"
#include <array>
#include <set>
#include <vector>

namespace Morris
{
	class MorrisField
	{
	private:
		MorrisField();
		MorrisField& operator=(const MorrisField& other)
		{
			_cells = other._cells;
			return *this;
		}

		const std::array<MorrisMarkerPtr, 24>& GetField() const;
		bool GetMarkerPosition(int& pos, const MorrisMarkerPtr marker) const;
		
		const MorrisMarkerPtr GetAt(int pos) const;
		bool SetAt(int pos, const MorrisMarkerPtr marker);
		bool SlideMarkerTo(int pos, const MorrisMarkerPtr marker);
		bool JumpMarkerTo(int pos, const MorrisMarkerPtr marker);
		bool EliminateMarker(const MorrisMarkerPtr marker);
		int GetMarkerCount(MorrisPlayer player) const;

	private:
		bool AreAdjacent(int pos1, int pos2) const;

	private:
		std::array<MorrisMarkerPtr, 24> _cells;

		const std::vector<std::set<int>> _adjacents =
		{
			{1, 9},				// 0
			{0, 2, 4},			// 1
			{1, 14},			// 2
			{4, 10},			// 3
			{1, 3, 5, 7},		// 4
			{4, 13},			// 5
			{7, 11},			// 6
			{4, 6, 8},			// 7
			{7, 12},			// 8
			{0, 10, 21},		// 9
			{3, 9, 11, 18},		// 10
			{6, 10, 15},		// 11
			{8, 13, 17},		// 12
			{5, 12, 14, 20},	// 13
			{2, 13, 23},		// 14
			{11, 16},			// 15
			{15, 17, 19},		// 16
			{12, 16},			// 17
			{10, 19},			// 18
			{16, 18, 20, 22},	// 19
			{13, 19},			// 20
			{9, 22},			// 21
			{19, 21, 23},		// 22
			{14, 22}			// 23
		};

		friend class MorrisGame;
	};
}

