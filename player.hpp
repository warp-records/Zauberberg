
#include "land.hpp"
#include "color.hpp"
#include "card.hpp"

#include <vector>
#include <iostream>
#include <algorithm>


#pragma once

struct Player {
	std::string const name;
	Color const color;

	std::vector<Territory*> terrs;
	std::vector<Card> cards;

	virtual std::string selectTerr() const = 0;

	int armies = 0;
	virtual int selectNumArmies() const = 0;

	//In addition to IO, we can implement move 
	//validity checks as virtual functions to make 
	//skip them for AI move generation; this may 
	//save processing power.

	//I feel like a genius :D
	//virtual std::vector<Territory*>::iterator ownsTerr(std::string const& terrName) const = 0;


	Player(std::string const& _name, Color _color) : 
		name{_name}, color{_color} {};
	/*
	Player(Color _color) : 
		color{_color} ();*/
};

struct User : public Player {

	using Player::Player;
	
	//IO
	std::string selectTerr() const {
		std::cout << "Select a territory:\n";

		std::string terr;
		std::cin >> terr;

		return terr;	
	}

	int selectNumArmies() const {
		std::cout << "Select a number of armies:\n";

		int numArmies;
		std::cin >> numArmies;

		if (armies < numArmies || armies < 0)
			throw std::exception();

		return armies;
	}

};

//One day
//struct AI : public Player {};