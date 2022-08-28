
#include "land.hpp"
#include "color.hpp"
#include "card.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>

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

	bool terrCaptured;

	//For defend command only
	int numDiceUsing;

	virtual std::unique_ptr<Command> getCommand(Game& game) = 0;

	Player(std::string const& name_, Color color_) : 
		name{name_}, color{color_} {};
};



struct User : public Player {

	using Player::Player;
	
	std::unique_ptr<Command> getCommand(Game& game);

private:
	//Human IO
	std::unique_ptr<Command> promptPlaceArmies(Game& game);
	std::unique_ptr<Command> promptFreeMove(Game& game);
	std::unique_ptr<Command> promptAttack(Game& game);
	std::unique_ptr<Command> promptDefend(Game& game);
	std::unique_ptr<Command> promptVictoryMove(Game& game);
	std::unique_ptr<Command> promptPlayCards(Game& game);

	Territory* terrFromStr(Game& game, std::string const& name);

	//Consider implementing later
	//bool promptContinueTurn(std::string const& message);
};

//One day
//struct AI : public Player {};