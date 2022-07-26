
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

	bool commandError = false;
	int armies = 0;

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
	Command* promptPlaceArmies();
};

//One day
//struct AI : public Player {};