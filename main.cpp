

#define VERSION "0.0.5"

#include <iostream>
#include "game.hpp"

#include <fstream>
#include <sstream>

void printTerrNeighbors();

int main() {

	std::cout << "Zauberberg - Rift84\n" << 
	"Version " << VERSION << "\n" << std::endl;

	Game game(2);

	while (!game.gameOver()) {
		game.doTurn();
	}

	std::cout << game.getWinnerName() << 
		" won the game!" <<	std::endl;

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

void outputPlayerTerritories() {
	Game game(2);

	std::ofstream out("playerTerritories.txt");

	std::stringstream plr1;
	plr1 << "Player 1's territories:\n\n";

	std::stringstream plr2;
	plr2 << "Player 2's territories:\n\n";

	for (auto& terr : game.getTerritories()) {

		if (terr.owner->name == "Player 1") {
			plr1 << terr.name << std::endl;
		} else {
			plr2 << terr.name << std::endl;
		}
	}

	out << plr1.str() << "\n\n" << plr2.str();
}