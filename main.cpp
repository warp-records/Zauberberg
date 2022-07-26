

#define VERSION "0.0.2"

#include <iostream>
#include "game.hpp"

#include <fstream>

void printTerrNeighbors();

int main() {

	std::cout << "Zauberberg - Rift84\n" << 
	"Version " << VERSION << "\n" << std::endl;

	Game game(1);

	return 0;
}


//Tester functions
void printTerrNeighbors() {
	Game game(1);

	std::cout << "Lists of territory neighbors:";

	for (auto& terr : game.getTerritories()){
		std::cout << "\n\n" << terr.name <<
		"'s neighbors:\n";


		for (auto nbPtr : terr.neighbors) {
			std::cout << "\n\t- " << nbPtr->name;
		}
	}

	std::cout << std::endl;
}