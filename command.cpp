
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"
#include <algorithm>
#include <random>

class Game;

bool PlaceArmy::Execute(Game& game) {
	if (player->color != terr->ownerColor)
		return false;

	if (numArmies > player->armies)
		return false;

	terr->armies += numArmies;
	player->armies -= numArmies;

	return true;
}

bool FreeMove::Execute(Game& game) {
	if (origin->ownerColor != player->color)
		return false;
	
	if (dest->ownerColor != player->color)
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
	if (attacker->armies - numArmies < 1)
		return false;

	if (attacker->ownerColor != player->color)
		return false;

	if (attacker->ownerColor == defender->ownerColor)
		return false;

	if (std::find(attacker->neighbors.begin(), 
		attacker->neighbors.end(), defender) == attacker->neighbors.end()) {
		return false;
	}

	
}

bool AttackExec::Execute(Game& game);


bool Defend::Execute(Game& game) {


	return true;
}