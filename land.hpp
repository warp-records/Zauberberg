
#include "color.hpp"
#include <vector>
#include <string>

#pragma once

/*
class Territory;

class Continent {
	std::string const name;
	std::vector<Territory> territories;

public:
	std::string getName() const { return name; }
	std::vector<Territory>& getTerritories() { return territories; }

	Continent(std::string _name, std::vector<Territory> _terr) : 
		territories{_terr}, name{_name} {};
	//std::string getName() { return name; }
};*/
enum Continent {
	NorthAmerica,
	SouthAmerica,
	Africa,
	Asia,
	Europe,
	Australia
};



class Territory {

	//Can't be made const unfortunately
	std::vector<Territory*> neighbors;

	Color ownerColor = Color::Neutral;
	unsigned armyCount = 0;

public:
	std::string const name;
	Continent const continent;

	Territory(std::string _name, Continent _cont) :
		name{_name}, continent{_cont} {};

	//Should only be called during initialization
	void addNeighbor(Territory*);

	unsigned getArmyCount() const { return armyCount; }
	Color getColor() const { return ownerColor; }
	std::vector<Territory*>& getNeighbors()  { return neighbors; }


	std::string getName() const { return name; }

};