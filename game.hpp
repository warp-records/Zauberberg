

#include "land.hpp"
#include "player.hpp"
#include "card.hpp"
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
	PlayCards,
	None
};

class Game {
	std::vector<std::unique_ptr<Player>> players;

	std::vector<Territory> territories;
	std::vector<Card> deck = std::vector<Card>(42);

	TurnPhase turnState = TurnPhase::None;
	int turnNum = 0;

	int cardPlays = 0;

	//Used during game initialization
	std::vector<Territory> genLandData();

	void execAttack();

	bool gameOver_ = false;
	std::string winnerName;

public:
	struct ATKST {
		Territory* origin;
		Territory* target;

		unsigned attackDie;
		unsigned defendDie;
	} attackState;

	Game(int numPlayers);

	void doTurn();

	int getCardPlays() { return cardPlays; }
	void incCardPlays() { cardPlays++; }

	//Expose for debugging purposes
	std::vector<std::unique_ptr<Player>>& getPlayers() { return players; }

	std::vector<Territory>& getTerritories() { return territories; }

	TurnPhase getTurnState() { return turnState; }

	static int rollDie();

	bool gameOver() { return gameOver_; }
	std::string getWinnerName() { return winnerName; }

	template <template<class ...> class Cont> void 
		discardCard(Cont<Card>& cards, Card card);
};


template <template<typename ...> typename Cont> void 
	Game::discardCard(Cont<Card>& cards, Card card) {

	typename Cont<Card>::iterator it = cards.begin();

	it = std::find(cards.begin(), cards.end(), card);

	deck.push_back(*it);

	cards.erase(it);
}

auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName);