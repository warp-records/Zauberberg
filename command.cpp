
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"
#include "game.hpp"
#include "std_extension_impl.hpp"
#include "card.hpp"
#include <algorithm>
#include <set>
#include <random>

class Game;

//void Game::discardCard<std::vector>(std::vector<Card>& cards, Card card);

bool PlaceArmy::Execute(Game& game) {
	if (terr->owner != player)
		return false;

	if (numArmies > player->armies)
		return false;

	terr->armies += numArmies;
	player->armies -= numArmies;

	return true;
}

bool FreeMove::Execute(Game& game) {
	if (origin->owner != player)
		return false;
	
	if (dest->owner != player)
		return false;

	if (origin->armies - numArmies < 1)
		return false;

	if (dest == origin)
		return false;

	origin->armies -= numArmies;
	dest->armies += numArmies;

	return true;
}

bool AttackInit::Execute(Game& game) {
	if (origin->armies == 1)
		return false;

	if (numDie == 0 || 
		numDie > std::min(origin->armies - 1, 3u)) {
		return false;
	}

	if (origin->owner != player)
		return false;

	if (std::find(origin->neighbors.begin(), 
		origin->neighbors.end(), target) == origin->neighbors.end()) {
		return false;
	}

	if (target->owner == player)
		return false;

	game.attackState = {
		origin, target, numDie, 0
	};

	return true;
}

bool DefendInit::Execute(Game& game) {
	if (numDie == 0 || 
		numDie > std::min(game.attackState.target->armies, 2u)) {
		return false;
	}

	game.attackState.defendDie = numDie;

	return true;
}

bool VictoryArmyMove::Execute(Game& game) {
	if (numArmies < game.attackState.attackDie || 
			numArmies > game.attackState.origin->armies - 1) {
		return false;
	}

	game.attackState.target->armies -= numArmies;
	game.attackState.origin->armies += numArmies;

	return true;
}



bool PlayCards::Execute(Game& game) {

	std::array<Card, 3> chosenCards;

	std::vector<Card> cardList = player->cards;

	try {
		for (int i = 0; i < 3; i++) {
			chosenCards[i] = strToCard(cardNames[i]);

			auto it = std::find(cardList.begin(),
				cardList.end(), chosenCards[i]);

			if (it == cardList.end())
				return false;

			cardList.erase(it);
		}
	} catch (...) {
		return false;
	}

	if (std_ext::count_unique(chosenCards.begin(), 
			chosenCards.end()) == 3) {
		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		return true;
	}

	if (std_ext::count_unique(chosenCards.begin(), 
		chosenCards.end()) == 0) {

		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		return true;
	}

	if (std::count(player->cards.begin(), 
		player->cards.end(), Card::Joker) >= 1) {

		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		return true;
	}

	//Still need to implement

	return false;
};


