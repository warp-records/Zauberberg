
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
enum class CmdStatus;

//void Game::discardCard<std::vector>(std::vector<Card>& cards, Card card);

CmdStatus EndTurn::Execute(Game& game) { 
	player->endTurn = true;

	return CmdStatus::Success;
};

CmdStatus PlaceArmy::Execute(Game& game) {
	if (terr->owner != player)
		return CmdStatus::PlayerNotOwner;

	if (numArmies > player->armies)
		return CmdStatus::NotEnoughArmies;

	terr->armies += numArmies;
	player->armies -= numArmies;

	return CmdStatus::Success;
}

CmdStatus FreeMove::Execute(Game& game) {
	if (origin->owner != player)
		return CmdStatus::PlayerNotOwner;
	
	if (dest->owner != player)
		return CmdStatus::PlayerNotOwner;

	if (origin->armies - numArmies < 1)
		return CmdStatus::NotEnoughArmies;

	if (dest == origin)
		return CmdStatus::DestIsOrigin;

	origin->armies -= numArmies;
	dest->armies += numArmies;

	return CmdStatus::Success;
}

CmdStatus AttackInit::Execute(Game& game) {
	if (origin->armies == 1)
		return CmdStatus::NotEnoughArmies;

	if (numDie == 0 || 
		numDie > std::min(origin->armies - 1, 3u)) {
		return CmdStatus::InvalidNumDie;
	}

	if (origin->owner != player)
		return CmdStatus::PlayerNotOwner;

	if (std::find(origin->neighbors.begin(), 
		origin->neighbors.end(), target) == origin->neighbors.end()) {
		return CmdStatus::TargetOutsideRange;
	}

	if (target->owner == player)
		return CmdStatus::SelfHarm;

	game.attackState = Game::ATKST{
		origin, target, numDie, 0
	};

	return CmdStatus::Success;
}

CmdStatus DefendInit::Execute(Game& game) {
	if (numDie == 0 || 
		numDie > std::min(game.attackState.target->armies, 2u)) {
		return CmdStatus::InvalidNumDie;
	}

	game.attackState.defendDie = numDie;

	return CmdStatus::Success;
}

CmdStatus VictoryArmyMove::Execute(Game& game) {
	if (numArmies < game.attackState.attackDie || 
			numArmies > game.attackState.origin->armies - 1) {
		return CmdStatus::InvalidNumArmies;
	}

	game.attackState.target->armies -= numArmies;
	game.attackState.origin->armies += numArmies;

	return CmdStatus::Success;
}



CmdStatus PlayCards::Execute(Game& game) {

	std::array<Card, 3> chosenCards;

	std::vector<Card> cardList = player->cards;

	bool validCardPlay = false;

	try {
		for (int i = 0; i < 3; i++) {
			chosenCards[i] = strToCard(cardNames[i]);

			auto it = std::find(cardList.begin(),
				cardList.end(), chosenCards[i]);

			if (it == cardList.end())
				return CmdStatus::InvalidCardPlay;

			cardList.erase(it);
		}
	} catch (...) {
		return CmdStatus::InvalidCardPlay;
	}

	if (std_ext::count_unique(chosenCards.begin(), 
			chosenCards.end()) == 3) {
		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		validCardPlay = true;
	}

	if (!validCardPlay && std_ext::count_unique(chosenCards.begin(), 
		chosenCards.end()) == 1) {

		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		validCardPlay = true;
	}

	if (!validCardPlay && std::count(player->cards.begin(), 
		player->cards.end(), Card::Joker) >= 1) {

		for (Card card : chosenCards)
			game.discardCard<std::vector>(player->cards, card);	

		validCardPlay = true;
	}
	
	if (!validCardPlay)
		return CmdStatus::InvalidCardPlay;

	if (game.getCardPlays() < 5) {
		player->armies += 4 + game.getCardPlays() * 2;
	} else if (game.getCardPlays() == 5) {
		player->armies += 15;
	} else {
		player->armies += game.getCardPlays() * 5 - 10;
	}

	game.incCardPlays();

	return CmdStatus::Success;
};


