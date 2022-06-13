#include "land.hpp"
#include "color.hpp"


#include <vector>

#pragma once

class Player {
	Color const color;
	std::vector<Territory*> territories;

	unsigned armyEntitlement = 0;
	unsigned armyCount = 5;

public:
	Player(Color _color, std::vector<Territory*> _terr) : 
		color{_color}, territories{_terr} {};
};