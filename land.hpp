
#include "color.hpp"
#include <vector>
#include <string>

#pragma once

class Territory;


struct Continent {
	std::string const name;
	std::vector<Territory> territories;

	Continent(std::string _name, std::vector<Territory> _terr) : 
		territories{_terr}, name{_name} {};

	//std::string getName() { return name; }
};



class Territory {
	//Just exposing the whole class for debugging
public:
	std::string const name;

	//Can't be const unfortunately, because
	//the member territories need to be initialized
	//in order to posess a pointer to them
	std::vector<Territory*> neighbors;

	Color ownerColor = Color::Neutral;
	unsigned armyCount = 0;

	Territory(std::string _name) :
		name{_name} {};

	//Should only be called during initialization
	void addNeighbor(Territory*);

	unsigned getArmyCount() const { return armyCount; }
	Color getColor() const { return ownerColor; }
	//std::vector<Territory* const>& getNeighbors()  { return neighbors; }


	std::string getName() const { return name; }

};