
#include "land.hpp"
#include "color.hpp"
#include "card.hpp"

#include <vector>

#pragma once

struct Player {
	Color const color;
	//int ownedArmies = 0;

	std::vector<Territory*> terrs;
	std::vector<Card> cards;


	/*
	unsigned armyEntitlement = 0;
	unsigned armyCount = 5;
	*/

	/*
	Player(Color _color) : 
		color{_color} ();*/
};