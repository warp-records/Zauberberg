

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <array>

#pragma once

class Game {
	std::vector<Player> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	Color turnColor = Color::Neutral;

	//Used during game initialization
	std::vector<Territory> genLandData();


public:
	Game(int numPlayers);

	void doTurn();

	std::vector<Territory>& getTerritories() { return territories; }
	Color getTurnColor() { return turnColor; }
};

