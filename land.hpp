
#include "color.hpp"
#include <vector>

#pragma once

class Territory;

class Continent {
	std::string const name;
	std::vector<Territory> const territories;

public:
	Continent(std::string _name, std::vector<Territory> _terr) : 
		name{_name}, territories{_terr} {};
};



class Territory {
	std::string const name;

	std::vector<Territory const*> const neighbors;

	Color ownerColor = Color::Neutral;
	unsigned armyCount = 0;

public:
	Territory(std::string _name, std::vector<Territory const*> _neighbors) :
		name{_name}, neighbors{_neighbors} {};

	//void attack();
	unsigned getArmyCount() { return armyCount; }
	Color getColor() { return ownerColor; }
	auto const& getNeighbors() { return neighbors; }
};