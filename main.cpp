
//Technically version 0 ig lol
#define VERSION "0.0.0"

#include <iostream>
#include "game.hpp"

#include <fstream>

int main() {

	std::cout << "Zauberberg - Rift84\n" << 
	"Version " << VERSION << std::endl;

	Game game;

	//std::string in;

	//while (true) {
		/*std::cout << "Enter a territory name " <<
		"and see what territories it borders:" << std::endl;

		std::cin >> in;
		std::cout << "\n\nNeighbors:\n";*/
		std::cout << "Lists of territory neighbors:\n\n";

		for (Continent const& cont : game.getContinents()) {
			for (Territory const& terr : cont.territories) {

				std::cout << "\n" << 
					terr.getName() << "'s neighbors:" << "\n\n";
				
				for (Territory* const neighbor : terr.neighbors) {
					std::cout << "\t- " << neighbor->getName() << "\n";
				}
			}
		}

		std::cout << std::endl;
	//}
}
