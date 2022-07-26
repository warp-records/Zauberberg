
#include "game.hpp"
#include "command.hpp"
#include "player.hpp"

Command* User::promptPlaceArmies(Game& game) {
	std::cout << name << "'s turn:\n" <<
	"Where would you like to place your armies?" << std::endl;

	std::string terrName;
	std::cin >> terrName;

	std::cout << "How many armies would you like to palce?\n";

	unsigned numArmies;
	std::cin >> numArmies;

	//Use with C++-20
	/*
	Territory* terr = std::ranges::find(terrs, terrName,
		{}, &Territory::name);
	*/

    Territory* terr = &(*std::find_if(
    	game.getTerritories().begin(), 
    	game.getTerritories().end(), 

        [&terrName](Territory& searchTerr) {
        	return searchTerr.name == terrName; 
        }));

	return new PlaceArmy(this, terr, numArmies);
}

Command* User::getCommand(Game& game) {
		std::cout << "\n";
		
		if (commandError) {
			std::cout << "The previous command yielded" << 
				" an error; try again." << std::endl;
		}

		switch (game.getTurnState()) {

			case (TurnPhase::PlacingArmies): {
				return promptPlaceArmies(game);
			};

			default: {
				std::cerr << "Error: invalid turn state; terminating." << 
					std::endl;
				return nullptr;
			}
		}
	}