#pragma once
#include <utility>
#include "Surface.h"
#include "Graphics.h"

class board {
public:
	enum class place
	{
		X,
		O,
		MPT
	};
	enum class gameoverStates {
		NoMPT,
		rowMatch,
		colMatch,
		crossMatch,
		NotOver
	};
	board();
	void show(Graphics& gfx) const;
	place getPlace(std::pair<int, int> pos);
	bool setPlace(std::pair<int, int> pos, place p);
	bool board::unsetPlace(std::pair<int, int> pos);
	place getResult();
	bool IsFull();
	std::vector<std::pair<int, int>> getEmptyPlaces() const;
	void reset();
private:
	bool isEmpty(std::pair<int, int> pos);
	bool checkGameover();
	place tablePlaces[3][3];
	gameoverStates winCond = gameoverStates::NotOver;
	int overPlace = -1;
	bool isFull = false;
	Surface O = { "Images\\O.bmp" };
	Surface X = { "Images\\X.bmp" };
};