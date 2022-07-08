
#include "color.hpp"
#include <vector>
#include <string>

#pragma once

class Territory;


struct Continent {
	std::string const name;
	std::vector<Territory> const territories;

	Continent(std::string _name, std::vector<Territory> _terr) : 
		name{_name} {};

	std::string getName() { return name; }
};



class Territory {
	std::string const name;

	//Can't be const unfortunately, because
	//the member territories need to be initialized
	//in order to posess a pointer to them
	std::vector<const Territory*> neighbors;

	Color ownerColor = Color::Neutral;
	unsigned armyCount = 0;


	Territory(std::string _name) :
		name{_name} {};

	//Should only be called during initialization
	void addNeighbor(Territory*);

	//void attack();
	unsigned getArmyCount() { return armyCount; }
	Color getColor() { return ownerColor; }
	std::vector<const Territory*>& getNeighbors() { return neighbors; }


	std::string getName() { return name; }

};