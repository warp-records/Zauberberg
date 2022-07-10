
#include "land.hpp"

void Territory::addNeighbor(Territory* territory) {
	neighbors.push_back(territory);
}