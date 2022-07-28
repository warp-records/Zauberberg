
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


//Note: will need to be changed since some
//turn phases require a move
struct EndTurn : Command {
	Player* player;

	bool Execute(Game& game) { 
		player->endTurn = true;
		return true;
	};

	EndTurn(Player* player_) : 
		player{player_} {};
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

struct FreeMove : Command {
	Player* player;

	Territory* origin;
	Territory* dest;
	unsigned numArmies;


	FreeMove(Player* player_, Territory* origin_, 
		Territory* dest_, unsigned numArmies_) :
		player{player_}, origin{origin_}, dest{dest_},
		numArmies{numArmies_} {};

	bool Execute(Game& game);
};



//Calls defend
struct AttackInit : Command {
	Player* player;

	Territory* origin;
	Territory* dest;
	unsigned numArmies;

	AttackInit(Player* player_, Territory* origin_, 
	Territory* dest_, unsigned numArmies_) :
	player{player_}, origin{origin_}, dest{dest_},
	numArmies{numArmies_} {};

	bool Execute(Game& game);
};

//Calls attack execute
struct Defend : Command {
	Player* player;

	Territory* attacker;

	bool Execute(Game& game);
}

//Finishes attack
struct AttackExec : Command {};