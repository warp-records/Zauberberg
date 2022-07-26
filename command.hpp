
#include "land.hpp"

#pragma once

class Game;
struct Player;
struct User;

//This design is going to be radically different 
struct Command {
	//virtual ~Command() = default;
	virtual bool Execute(Game& game) = 0;
};


struct PlaceArmy : Command {
	Player* player;
	Territory* terr;
	unsigned numArmies;

	PlaceArmy(Player* player_, 
		Territory* terr_, unsigned numArmies_) :
	player{player_}, terr{terr_}, numArmies{numArmies_} {};

	bool Execute(Game& game);
};