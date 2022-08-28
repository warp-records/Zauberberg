
#include "land.hpp"
#include <array>

#pragma once

class Game;
struct Player;
struct User;

enum class CmdStatus {
	Success,
	InvalidNumArmies,
	NotEnoughArmies,
	SelfHarm,
	PlayerNotOwner,
	DestIsOrigin,
	TargetOutsideRange,
	InvalidNumDie,
	InvalidCardPlay,
	IOError
};

struct Command {
	Player* player;

	virtual CmdStatus Execute(Game& game) = 0;

	Command(Player& player_) : player{&player_} {};
};

struct EndTurn : Command {

	CmdStatus Execute(Game& game);
	EndTurn(Player& player_) : 
		Command{player_} {};
};


struct PlaceArmy : Command {

	Territory* terr;
	unsigned numArmies;

	PlaceArmy(Player& player_, 
		Territory& terr_, unsigned numArmies_) :
	Command{player_}, terr{&terr_}, numArmies{numArmies_} {};

	CmdStatus Execute(Game& game);
};

struct FreeMove : Command {

	Territory* origin;
	Territory* dest;
	unsigned numArmies;

	FreeMove(Player& player_, Territory& origin_, 
		Territory& dest_, unsigned numArmies_) :
		Command{player_}, origin{&origin_}, dest{&dest_},
		numArmies{numArmies_} {};

	CmdStatus Execute(Game& game);
};



struct AttackInit : Command {

	Territory* origin;
	Territory* target;
	unsigned numDie;

	AttackInit(Player& player_, Territory& origin_, 
		Territory& target_, unsigned numDie_) :
		Command{player_}, origin{&origin_}, target{&target_},
		numDie{numDie_} {};

	CmdStatus Execute(Game& game);
};

struct DefendInit : Command {

	unsigned numDie;

	DefendInit(Player& player_, unsigned numDie_) :
		Command{player_}, numDie{numDie_} {};

	CmdStatus Execute(Game& game);
};



struct VictoryArmyMove : Command {

	unsigned numArmies;

	VictoryArmyMove(Player& player_, unsigned numArmies_) : 
		Command{player_}, numArmies{numArmies_} {};

	CmdStatus Execute(Game& game);
};

struct PlayCards : Command {
	
	std::array<std::string, 3> cardNames;

	PlayCards(Player& player_, std::array<std::string, 3> cardNames_) : 
		Command{player_}, cardNames{cardNames_} {};

	CmdStatus Execute(Game& game);
};
