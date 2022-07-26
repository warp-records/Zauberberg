
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
	//int ownedArmies = 0;

	std::vector<Territory*> terrs;
	std::vector<Card> cards;

	//virtual std::string selectTerr() const = 0;

	//We can implement move validity checks as
	//virtual functions to make them optional for
	//an AI; this may save processing power.

	//I feel like a genius :D
	//virtual bool ownsTerr(std::string const& terrName) const = 0;


	Player(std::string const& _name, Color _color) : 
		name{_name}, color{_color} {};
	/*
	Player(Color _color) : 
		color{_color} ();*/
};

struct User : public Player {

	/*
	std::string selectTerr() const {
		std::cout << "Select a territory:\n";

		std::string terr;
		std::cin >> terr;

		return terr;	
	}*/

	/*
	bool ownsTerr(std::string const& searchName) const {

		return std::find_if(terrs.begin(), terrs.end(), 
			[&searchName](Territory const* terr) { return terr->name == searchName; }) != terrs.end();
	}*/

	using Player::Player;
};

//One day
//struct AI : public Player {};