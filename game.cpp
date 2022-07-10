
#include "game.hpp"
#include <array>
#include <vector>

Game::Game() {

	//Just try to ignore all this code because it's garbage

	//You'll have to read land_dat.hpp to understand this
	for (auto cont : LandData::LandNames) {
		std::vector<Territory> territories;

		for (std::string terrName : cont.second) {
			territories.push_back(Territory(terrName));
		}

		continents.push_back(Continent(cont.first, territories));
	}
	
	//Unpack the neighbor data
	for (int cont = LandData::data.size() - 1; cont >= 0; cont--) {
		for (int terr = LandData::data[cont].size() - 1; terr >= 0; terr--) {
			for (auto nbCord : LandData::data[cont][terr]) {

				continents[cont].territories[terr].addNeighbor(&continents[nbCord.first].territories[nbCord.second]);
				continents[nbCord.first].territories[nbCord.second].addNeighbor(&continents[cont].territories[terr]);
			}
		}
	}



};

