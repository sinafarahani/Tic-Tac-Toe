#pragma once
#include "Board.h"
#include <random>
#include <array>

class ai
{
public:
	ai(const board::place& aiSymbol);
	std::pair<int, int> run(board& brd);
private:
	void update(board& brd);
	std::pair<int, int> atkOrDef(std::array<std::vector<int>, 3> target);
	std::pair<int, int> PlaceInRandomCorner();
	const board::place& aiSymbol;
	board::place state[3][3];
	std::vector<std::pair<int, int>> emptyPlaces;
	std::array<std::vector<int> , 3> aiPlaces;
	std::array<std::vector<int> , 3> huPlaces;
	bool centerPlaced = false;
};