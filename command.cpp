
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"

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

	if (numArmies >= origin->armies)
		return false;

	if (dest == origin)
		return false;

	origin->armies -= numArmies;
	dest->armies += numArmies;

	return true;
}