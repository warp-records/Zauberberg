
#include "land.hpp"
#include "color.hpp"
#include "card.hpp"

#include <vector>

#pragma once

struct Player {
	Color const color;
	
	std::vector<Territory*> ownedTerrs;
	std::vector<Card> cards;

	/*
	unsigned armyEntitlement = 0;
	unsigned armyCount = 5;
	*/

	/*
	Player(Color _color) : 
		color{_color} ();*/
};