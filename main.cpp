
#define VERSION "0.0.1"

#include <iostream>
#include "game.hpp"

#include <fstream>

void genData();

int main() {

	std::cout << "Zauberberg - Rift84\n" << 
	"Version " << VERSION << std::endl;

	Game game;

	std::string in;

	while (true) {
		std::cout << "Enter a territory name " <<
		"and see what territories it borders:" << std::endl;

		std::cin >> in;
		std::cout << "\n\nNeighbors:\n";

		for (Continent const& cont : game.getContinents()) {
			for (Territory const& terr : cont.territories) {

				if (terr.getName() == in) {
					for (Territory* const neighbor : terr.neighbors) {
						std::cout << neighbor->getName() << "\n";
					}

					break;
				}
			}
		}

		std::cout << "\n" << std::endl;

	}
}
