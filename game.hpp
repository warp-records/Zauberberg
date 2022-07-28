

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
#include "command.hpp"
#include <vector>
#include <array>
#include <memory>

#pragma once

enum class TurnPhase {
	PlacingArmies,
	FreeMove,
	Attack,
	None
};

class Game {
	std::vector<std::unique_ptr<Player>> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	TurnPhase turnState = TurnPhase::None;
	int turnNum = 0;

	//Apparently this is the simplest way
	//to use C++'s modern random library lol..
	std::random_device rd;
	std::mt19937 gne(rd);
	std::uniform_int_distribtuion<> die(1, 6);

	//Used during game initialization
	std::vector<Territory> genLandData();

public:
	Game(int numPlayers);

	void doTurn();

	std::vector<Territory>& getTerritories() { return territories; }
	//Color getTurnColor() const { return static_cast<Color>(turnNum); }

	TurnPhase getTurnState() { return turnState; };

	int rollDie() { return die(gen); }
};

//Misc function
auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName);