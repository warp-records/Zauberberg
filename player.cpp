
#include "game.hpp"
#include "command.hpp"
#include "player.hpp"


//Command* User::promptPlaceArmies(Game& game);
//Command* User::promptFreeMove(Game& game);

Territory* terrFromStr(Game& game, std::string const& name);

//Add option to end turn later
Command* User::getCommand(Game& game) {

	endTurn = false;

	std::cout << "\n";

	if (commandError) {
		std::cout << "The previous command yielded" << 
			" an error; try again." << std::endl;
		commandError = false;
	}

	switch (game.getTurnState()) {

		case (TurnPhase::PlacingArmies): {
			return promptPlaceArmies(game);
		};

		case (TurnPhase::FreeMove): {
			return promptFreeMove(game);
		};

		case (TurnPhase::AttackInit): {
			return promptAttack(game);
		};

		default: {
			std::cerr << "Error: invalid turn state; terminating." << 
				std::endl;
			return nullptr;
		}
	}
}


Command* User::promptPlaceArmies(Game& game) {
	std::cout << name << "'s turn:\n" <<
	"Where would you like to place your armies?" << std::endl;

	std::string terrName;
	std::cin >> terrName;

	std::cout << "How many armies would you like to palce?" 
		"\t(" << armies << " armies left)" << std::endl;

	unsigned numArmies;
	std::cin >> numArmies;

	Territory* terr = terrFromStr(game, terrName);

	return new PlaceArmy(this, terr, numArmies);
}


Command* User::promptFreeMove(Game& game) {
	std::cout << "\nWould you like to use a free move? (y/n)" <<
		std::endl;

	char choice;
	std::cin >> choice;

	if (choice == 'n') {
		return new EndTurn(this);

	} else if (choice != 'y') {
		commandError = true;

		return promptFreeMove(game);
	}

	std::cout << "\nWhat territory would you like to " <<
		"move armies from?" << std::endl;

	std::string origin;
	std::cin >> origin;

	std::cout << "\nWhat territory do you want " <<
		"to move them to?" << std::endl;

	std::string dest;
	std::cin >> dest;

	std::cout << "\nHow many armies do you want " <<
		"to move?" << std::endl;

	unsigned numArmies;
	std::cin >> numArmies;


	Territory* originPtr = terrFromStr(game, origin);
	Territory* destPtr = terrFromStr(game, dest);


	return new FreeMove(this, originPtr, destPtr, numArmies);
}

Command* User::promptAttack(Game& game) {
	std::cout << "Would you like attack? (y/n)" <<
		std::endl;

	char choice;
	std::cin >> choice;

	if (choice == 'n') {
		return new EndTurn(this);

	} else if (choice != 'y') {
		commandError = true;

		return promptAttack(game);
	}

	std::cout << "\nWhat territory would you like to " <<
		"attack from?" << std::endl;

	std::string origin;
	std::cin >> origin;

	std::cout << "\nWhat territory do you want to attack?"
		 << std::endl;

	std::string target;
	std::cin >> target;

	std::cout << "\nHow many die would you like to " <<
		"attack with?" << std::endl;

	unsigned numDie;
	std::cin >> numDie;


	Territory* originPtr = terrFromStr(game, origin);
	Territory* targetPtr = terrFromStr(game, target);

	return new AttackInit(this, originPtr, targetPtr, numDie);
}


Command* User::promptDefend(Game& game) {

	std::cout << "\nHow many die would you like to " <<
	"defend with?" << std::endl;

	unsigned numDie;
	std::cin >> numDie;

	return new DefendInit(this, numDie);
}

/*
Command* User::promptVictoryMove(Game& game) {
	return nullptr;
};
*/

Territory* User::terrFromStr(Game& game, std::string const& name) {
	//Use post C++20
	/*
	Territory* terr = std::ranges::find(terrs, terrName,
		{}, &Territory::name);
	*/

	//Use pre C++20
    Territory* terr = &(*std::find_if(
    	game.getTerritories().begin(), 
    	game.getTerritories().end(), 

        [&name](Territory& currentTerr) {
        	return currentTerr.name == name; 
        }));

    return terr;
}