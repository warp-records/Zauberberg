

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <array>
#include <memory>

#pragma once

class Game {
	//TODO: prevent memory leaks
	//Can we use unique_ptr for this?
	std::vector<std::unique_ptr<Player>> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	int turnNum = 0;

	//Used during game initialization
	std::vector<Territory> genLandData();


public:
	Game(int numPlayers);

	void doTurn();

	std::vector<Territory>& getTerritories() { return territories; }
	Color getTurnColor() const { return static_cast<Color>(turnNum); }

};

//Misc function
auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName);