
#include "land.hpp"
#include <array>

#pragma once

class Game;
struct Player;
struct User;


struct Command {
	virtual bool Execute(Game& game) = 0;
};

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



struct AttackInit : Command {
	Player* player;

	Territory* origin;
	Territory* target;
	unsigned numDie;

	AttackInit(Player* player_, Territory* origin_, 
		Territory* target_, unsigned numDie_) :
		player{player_}, origin{origin_}, target{target_},
		numDie{numDie_} {};

	bool Execute(Game& game);
};

struct DefendInit : Command {
	Player* player;

	unsigned numDie;

	DefendInit(Player* player_, unsigned numDie_) :
		player{player_}, numDie{numDie_} {};

	bool Execute(Game& game);
};



struct VictoryArmyMove : Command {
	Player* player;

	unsigned numArmies;

	VictoryArmyMove(Player* player_, unsigned numArmies_) : 
		player{player_}, numArmies{numArmies_} {};

	bool Execute(Game& game);
};

struct PlayCards : Command {
	Player* player;
	std::array<std::string, 3> cardNames;

	PlayCards(Player* player_, std::array<std::string, 3> cardNames_) : 
		player{player_}, cardNames{cardNames_} {};

	bool Execute(Game& game);
};
