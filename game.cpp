
#include "game.hpp"
#include "land_dat.hpp"
#include <array>
#include <vector>

Game::Game() {

	std::vector<Continent> continents;

	//You'll have to read land_dat.hpp to understand this
	for (auto cont : LandData::continents) {
		std::vector<Territory> territories;

		for (std::string terrName : cont) {
			territories.push_back(Territory(terrName));
		}

		continents.push_back(Continent(territories));
	}
	
	//Unpack the neighbor data
	for (int cont = data.size() - 1; cont >= 0; cont--) {
		for (int terr = data[cont].size() - 1; terr >= 0; terr--) {
			for (auto nbCord : data[cont][terr]) {
				//data.at(nbCord.first).at(nbCord.second).push_back(std::make_pair(cont, terr));
				continents[cont][terr].addNeighbor(&continents[nbCord.first][nbCord.second]);
				continents[nbCord.first][nbCord.second].addNeighbor(&continents[cont][terr]);
			}
		}
	}
};


