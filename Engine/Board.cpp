#include "Board.h"

board::board()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tablePlaces[i][j] = place::MPT;
		}
	}
}

void board::show(Graphics& gfx) const
{
	
	for (int j = gfx.ScreenHeight / 3 - 1; j <= gfx.ScreenHeight / 3 + 1; j++) {
		for (int i = 10; i < gfx.ScreenWidth - 10; i++) {
			gfx.PutPixel(i, j, Colors::White);
		}
	}
	for (int j = 2 * gfx.ScreenHeight / 3 - 1; j <= 2 * gfx.ScreenHeight / 3 + 1; j++) {
		for (int i = 10; i < gfx.ScreenWidth - 10; i++) {
			gfx.PutPixel(i, j, Colors::White);
		}
	}
	for (int j = 10; j < gfx.ScreenHeight - 10; j++) {
		for (int i = gfx.ScreenWidth / 3 - 1; i <= gfx.ScreenWidth / 3 + 1; i++) {
			gfx.PutPixel(i, j, Colors::White);
		}
	}
	for (int j = 10; j < gfx.ScreenHeight - 10; j++) {
		for (int i = 2 * gfx.ScreenWidth / 3 - 1; i <= 2 * gfx.ScreenWidth / 3 + 1; i++) {
			gfx.PutPixel(i, j, Colors::White);
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablePlaces[i][j] == place::X) {
				gfx.DrawSprite(j * gfx.ScreenWidth / 3 + 10, i * gfx.ScreenHeight / 3 + 10, X, SpriteEffect::Chroma(Colors::White));
			}
			if (tablePlaces[i][j] == place::O) {
				gfx.DrawSprite(j * gfx.ScreenWidth / 3 + 10, i * gfx.ScreenHeight / 3 + 10, O, SpriteEffect::Chroma(Colors::White));
			}
		}
	}
}

bool board::isEmpty(std::pair<int, int> pos)
{
	return tablePlaces[pos.first][pos.second] == place::MPT;
}

board::place board::getPlace(std::pair<int, int> pos)
{
	return tablePlaces[pos.first][pos.second];
}

bool board::setPlace(std::pair<int, int> pos, place p)
{
	if (isEmpty(pos)) {
		tablePlaces[pos.first][pos.second] = p;
		return true;
	}
	return false;
}

bool board::unsetPlace(std::pair<int, int> pos)
{
	if (!isEmpty(pos)) {
		tablePlaces[pos.first][pos.second] = place::MPT;
		return true;
	}
	return false;
}

bool board::checkGameover()
{
	
	if ((tablePlaces[0][0] == tablePlaces[1][1]) && (tablePlaces[1][1] == tablePlaces[2][2])) {
		winCond = gameoverStates::crossMatch;
		return true;
	}
	else if ((tablePlaces[2][0] == tablePlaces[1][1]) && (tablePlaces[1][1] == tablePlaces[0][2])) {
		winCond = gameoverStates::crossMatch;
		return true;
	}
	for (int i = 0; i < 3; i++) {
		if ((tablePlaces[i][0] == tablePlaces[i][1]) && (tablePlaces[i][1] == tablePlaces[i][2])) {
			winCond = board::gameoverStates::rowMatch;
			overPlace = i;
			return true;
		}
		if ((tablePlaces[0][i] == tablePlaces[1][i]) && (tablePlaces[1][i] == tablePlaces[2][i])) {
			winCond = board::gameoverStates::colMatch;
			overPlace = i;
			return true;
		}
	}
	bool isFull = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablePlaces[i][j] == place::MPT) {
				isFull = false;
			}
		}
	}
	if (isFull) {
		winCond = board::gameoverStates::NoMPT;
		this->isFull = true;
		return true;
	}
	return false;
}

board::place board::getResult()
{
	if (checkGameover()) {
		switch (winCond)
		{
		case board::gameoverStates::NoMPT:
			return board::place::MPT;
			break;
		case board::gameoverStates::rowMatch:
			return tablePlaces[overPlace][0];
			break;
		case board::gameoverStates::colMatch:
			return tablePlaces[0][overPlace];
			break;
		case board::gameoverStates::crossMatch:
			return tablePlaces[1][1];
			break;
		case board::gameoverStates::NotOver:
			return board::place::MPT;
			break;
		default:
			return board::place::MPT;
			break;
		}
	}
	return board::place::MPT;
}

bool board::IsFull()
{
	return isFull;
}

std::vector<std::pair<int, int>> board::getEmptyPlaces() const
{
	std::vector<std::pair<int, int>>MPT;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (tablePlaces[i][j] == place::MPT) {
				MPT.push_back(std::make_pair(i, j));
			}
		}
	}
	return MPT;
}

void board::reset()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tablePlaces[i][j] = place::MPT;
		}
	}
	winCond = gameoverStates::NotOver;
	overPlace = -1;
	isFull = false;
}
