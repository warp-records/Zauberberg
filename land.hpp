
#include "color.hpp"
#include <algorithm>
#include <vector>
#include <string>

#pragma once

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

	std::vector<Territory*> neighbors;

	Territory(std::string _name, Continent _cont) :
	name{_name}, continent{_cont} {};

};

