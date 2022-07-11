

#include "land.hpp"
#include "player.hpp"
#include <array>

#pragma once

class Game {
	//?
	std::vector<Continent> continents;

public:
	Game();

	std::vector<Continent>& getContinents() { return continents; }
};