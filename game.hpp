

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
//#include "command.hpp"
#include <vector>
#include <array>
#include <memory>
#include <random>

#pragma once

enum class TurnPhase {
	PlacingArmies,
	FreeMove,
	AttackInit,
	DefendInit,
	VictoryArmyMove,
	None
};

class Game {
	std::vector<std::unique_ptr<Player>> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	TurnPhase turnState = TurnPhase::None;
	int turnNum = 0;

	//Used during game initialization
	std::vector<Territory> genLandData();

	void attack();

public:
	struct ATKST {
		Territory* origin;
		Territory* target;

		unsigned attackDie;
		unsigned defendDie;
	} attackState;

	Game(int numPlayers);

	void doTurn();

	std::vector<Territory>& getTerritories() { return territories; }

	TurnPhase getTurnState() { return turnState; };

	int rollDie();
};


auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName);