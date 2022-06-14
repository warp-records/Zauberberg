
#include "color.hpp"
#include <vector>
#include <string>

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

	//Can't be const unfortunately, because
	//the member territories need to be initialized
	//in order to posess a pointer to them
	std::vector<const Territory*> neighbors;

	Color ownerColor = Color::Neutral;
	unsigned armyCount = 0;

public:
	Territory(std::string _name) :
		name{_name} {};

	//Should only be called during initialization
	void addNeighbor(Territory const*);

	//void attack();
	unsigned getArmyCount() { return armyCount; }
	Color getColor() { return ownerColor; }
	auto const& getNeighbors() { return neighbors; }
};