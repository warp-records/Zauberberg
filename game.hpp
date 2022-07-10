

#include "land.hpp"
#include "player.hpp"
#include <array>

#pragma once

class Game {

	std::vector<Continent> continents;

public:
	Game();

	std::vector<Continent> const& getContinents() const { return continents; }
};