
#include "game.hpp"
#include "land_dat.hpp"
//#include <algorithm>
#include <map>
#include <array>
#include <vector>

Game::Game(/*int numPlayers*/) {
	//players = std::vector<Player>(numPlayers)

	territories = genLandData();
	
	/*
	//Initialize deck
	std::fill(deck.begin(), deck.begin()+13, Card::Horsemen);
	std::fill(deck.begin()+14, deck.begin()+27, Card::Cannon);
	std::fill(deck.begin()+28, deck.begin()+41, Card::Soldier);
	std::random_shuffle(deck.begin(), deck.end());


	std::vector<Territory*> terrPtrStack;
	for (Continent const& cont : continents) {
		for (Territory const& terr : continents.get)
	}

	Player* plr = players.begin();

	//Note: implement card land association later
	while (!vector.empty()) {
		plr->cards.push_back(deck.pop_back());
		plr->

		plr++;
		if (plr == players.end())
			plr = players.begin();
	}*/
};





std::vector<Territory> Game::genLandData() {
	//Just try to ignore all this code because it's garbage
	std::vector<Territory> territories;

	std::map<std::string, Continent> const contNameMap {
		{"North America", NorthAmerica},
		{"South America", SouthAmerica},
		{"Africa", Africa},
		{"Asia", Asia},
		{"Europe", Europe},
		{"Australia", Australia}
	};

	std::array<int, 6> contNumOffs {{
		0, 9, 13, 20, 26, 38
	}};



	//You'll have to read land_dat.hpp to understand this
	for (auto cont : LandData::LandNames) {

		for (std::string terrName : cont.second) {
			territories.push_back(Territory(terrName, 
				contNameMap.at(cont.first)));
		}

		//continents.push_back(Continent(cont.first, territories));
	}
	
	//Unpack the neighbor data
	for (int cont = LandData::data.size() - 1; cont >= 0; cont--) {
		for (int terr = LandData::data[cont].size() - 1; terr >= 0; terr--) {
			for (auto nbCord : LandData::data[cont][terr]) {

				territories[contNumOffs.at(cont)+terr].addNeighbor(&territories[contNumOffs.at(nbCord.first)+nbCord.second]);
				territories[contNumOffs.at(nbCord.first)+nbCord.second].addNeighbor(&territories[contNumOffs.at(cont)+terr]);
			}
		}
	}

	return territories;
}