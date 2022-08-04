
#include "land.hpp"
#include "color.hpp"
#include "card.hpp"
#include <vector>
#include <iostream>
#include <algorithm>


#pragma once

enum class TurnPhase;
struct Command;
class Game;

struct Player {
	std::string const name;
	Color const color;

	std::vector<Territory*> terrs;
	std::vector<Card> cards;

	bool endTurn = false;
	bool commandError = false;
	int armies = 0;

	//For defend command only
	int numDiceUsing;

	virtual Command* getCommand(Game& game) = 0;


	Player(std::string const& _name, Color _color) : 
		name{_name}, color{_color} {};
	/*
	Player(Color _color) : 
		color{_color} ();*/
};



struct User : public Player {

	using Player::Player;
	
	Command* getCommand(Game& game);

private:
	//Human IO
	Command* promptPlaceArmies(Game& game);
	Command* promptFreeMove(Game& game);
	Command* promptAttack(Game& game);
	Command* promptDefend(Game& game);

	Territory* terrFromStr(Game& game, std::string const& name);

	//Consider implementing later
	//bool promptContinueTurn(std::string const& message);
};

//One day
//struct AI : public Player {};