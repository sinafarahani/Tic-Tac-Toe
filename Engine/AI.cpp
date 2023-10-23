#include "AI.h"

ai::ai(const board::place& aiSymbol)
	:
	aiSymbol(aiSymbol)
{
}

std::pair<int,int> ai::run(board& brd)
{
	update(brd);
	std::pair<int, int> pa = std::make_pair(1, 1);
	if (state[1][1] == board::place::MPT) {
		centerPlaced = true;
		return pa;
	}
	pa = atkOrDef(aiPlaces);
	if (pa != std::make_pair(1, 1)) {
		return pa;
	}
	pa = atkOrDef(huPlaces);
	if (pa != std::make_pair(1, 1)) {
		return pa;
	}
	if (emptyPlaces.size() <= 2) {
		return emptyPlaces.back();
	}
	if (centerPlaced && aiSymbol == board::place::O) {
		return PlaceInRandomCenter();
	}
	return PlaceInRandomCorner();
}

void ai::update(board& brd)
{
	emptyPlaces.clear();
	for (int i = 0; i < 3; i++) {
		aiPlaces[i].clear();
		huPlaces[i].clear();
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			state[i][j] = brd.getPlace(std::make_pair(i, j));
			if (brd.getPlace(std::make_pair(i, j)) == board::place::MPT)
				emptyPlaces.push_back(std::make_pair(i, j));
			else if (brd.getPlace(std::make_pair(i, j)) == aiSymbol)
				aiPlaces[i].push_back(j);
			else
				huPlaces[i].push_back(j);
		}
	}
}

std::pair<int, int> ai::atkOrDef(std::array<std::vector<int>, 3> target)
{
	for (int i = 0; i < 3; i++) {
		if (target[i].size() > 1) {
			int j = 0;
			while (target[i].at(j) == j) {
				j++;
				if (j == 2)
					break;
			}
			if (state[i][j] == board::place::MPT)
				return std::make_pair(i, j);
		}
	}
	for (const auto& i : target[0]) {
		for (const auto& j : target[1]) {
			if (i == j) {
				if (state[2][i] == board::place::MPT) {
					return std::make_pair(2, i);
				}
			}
		}
	}
	for (const auto& i : target[1]) {
		for (const auto& j : target[2]) {
			if (i == j) {
				if (state[0][i] == board::place::MPT) {
					return std::make_pair(0, i);
				}
			}
		}
	}
	for (const auto& i : target[0]) {
		for (const auto& j : target[2]) {
			if (i == j) {
				if (state[1][i] == board::place::MPT) {
					return std::make_pair(1, i);
				}
			}
		}
	}
	if (centerPlaced || target == huPlaces) {
		
		if (!target[0].empty())
		{
			for (const auto& tar : target[0]) {
				if (tar == 0) {
					if (state[2][2] == board::place::MPT) {
						return std::make_pair(2, 2);
					}
				}
				else if (tar == 2) {
					if (state[2][0] == board::place::MPT) {
						return std::make_pair(2, 0);
					}
				}
			}
		}
		if (!target[2].empty())
		{
			for (const auto& tar : target[2]) {
				if (tar == 0) {
					if (state[0][2] == board::place::MPT) {
						return std::make_pair(0, 2);
					}
				}
				else if (tar == 2) {
					if (state[0][0] == board::place::MPT) {
						return std::make_pair(0, 0);
					}
				}
			}
		}
	}
	return std::make_pair(1, 1);
}

std::pair<int, int> ai::PlaceInRandomCorner()
{
	std::vector<std::pair<int, int>> corners;
	for (const auto& corner : emptyPlaces) {
		if (corner == std::make_pair(0, 0)) {
			corners.push_back(std::make_pair(0, 0));
		}if (corner == std::make_pair(0, 2)) {
			corners.push_back(std::make_pair(0, 2));
		}if (corner == std::make_pair(2, 0)) {
			corners.push_back(std::make_pair(2, 0));
		}if (corner == std::make_pair(2, 2)) {
			corners.push_back(std::make_pair(2, 2));
		}
	}
	if (!corners.empty()) {
		std::vector<std::pair<int, int>> sample;
		std::sample(
			corners.begin(),
			corners.end(),
			std::back_inserter(sample),
			1,
			std::mt19937{ std::random_device{}() }
		);
		return sample.at(0);
	}
}

std::pair<int, int> ai::PlaceInRandomCenter()
{
	std::vector<std::pair<int, int>> centers;
	for (const auto& corner : emptyPlaces) {
		if (corner == std::make_pair(0, 1)) {
			centers.push_back(std::make_pair(0, 1));
		}if (corner == std::make_pair(1, 2)) {
			centers.push_back(std::make_pair(1, 2));
		}if (corner == std::make_pair(1, 0)) {
			centers.push_back(std::make_pair(1, 0));
		}if (corner == std::make_pair(2, 1)) {
			centers.push_back(std::make_pair(2, 1));
		}
	}
	if (!centers.empty()) {
		std::vector<std::pair<int, int>> sample;
		std::sample(
			centers.begin(),
			centers.end(),
			std::back_inserter(sample),
			1,
			std::mt19937{ std::random_device{}() }
		);
		return sample.at(0);
	}
}
