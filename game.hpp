

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
#include <vector>
#include <array>

#pragma once

class Game {
	//TODO: prevent memory leaks
	//Can we use unique_ptr for this?
	std::vector<Player*> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	int turnNum = 0;

	//Used during game initialization
	std::vector<Territory> genLandData();


public:
	Game(int numPlayers);

	void doTurn();

	std::vector<Territory>& getTerritories() { return territories; }
	Color getTurnColor() { return static_cast<Color>(turnNum); }



	//Weird, temporary debug IO:
	//Territory no, num armies
	/*
	std::pair<int, int> promptArmies() {
		std::out << "Enter where you would like to place armies:" <<
		"\nOptions: ";
	}*/
};

//Misc function
auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName);