

#include "land.hpp"
#include "player.hpp"
#include <array>

#pragma once

enum class Card {
	Horsemen,
	Cannon,
	Soldier,
	Joker
};

class Game {	
	//std::vector<Player> players;

	std::vector<Territory> territories;
	//std::vector<Card> deck(42);

	//Used during game initialization
	std::vector<Territory> genLandData();


public:
	Game();

	//std::vector<Territory>& getTerritories() { return territories; }
};

