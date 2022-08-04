
#include "color.hpp"
#include <algorithm>
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
struct Player;

enum Continent {
	NorthAmerica,
	SouthAmerica,
	Africa,
	Asia,
	Europe,
	Australia
};

struct Territory {
	std::string const name;
	Continent const continent;

	Player* owner;
	unsigned armies = 0;

	//Members should only be added and removed during
	//game initialization; unfortunately, can't be made const
	std::vector<Territory*> neighbors;

	Territory(std::string _name, Continent _cont) :
	name{_name}, continent{_cont} {};

	
	//I forget... do I need to remove this?
	//std::vector<Territory*>& getNeighbors()  { return neighbors; }

};

