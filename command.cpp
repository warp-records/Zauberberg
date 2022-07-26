
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"

class Game;

bool PlaceArmy::Execute(Game& game) {
	//Make an exception for this during game
	//initialization
	if (player->color != terr->ownerColor)
		return false;

	if (numArmies > player->armies)
		return false;

	terr->armies += numArmies;

	return true;
}