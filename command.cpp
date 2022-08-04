
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"
#include "game.hpp"
#include <algorithm>
#include <random>

class Game;

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

//bool AttackExec::Execute(Game& game);


bool DefendInit::Execute(Game& game) {
	if (numDie == 0 || 
		numDie > std::min(game.attackState.target->armies - 1, 2u)) {
		return false;
	}

	game.attackState.defendDie = numDie;

	return true;
}