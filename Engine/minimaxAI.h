#pragma once

#include <algorithm>

#include "Board.h"

class minimaxAi
{
public:
	minimaxAi( const board::place& aiSymbol, const board::place& huSymbol);
	std::pair<int, int> run(board& b);
private:
	std::pair<int, std::pair<int, int>> minimax_optimization(board b, const board::place marker, int depth, int alpha, int beta);
	const board::place& aiSymbol;
	const board::place& huSymbol;
};