
#include "game.hpp"
#include "land_dat.hpp"
#include "land.hpp"
#include "player.hpp"
#include "command.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <map>
#include <memory>
#include <array>
#include <vector>

auto searchTerrName(
	std::vector<Territory*> const& terrs, std::string const& searchName) {

	return std::find_if(terrs.begin(), terrs.end(), 
			[&searchName](Territory const* terr) { return terr->name == searchName; });
}


Game::Game(int numPlayers) {
	if (numPlayers < 1 || 6 < numPlayers)
		throw std::exception();

	territories = genLandData();

	std::fill(deck.begin(), deck.begin()+13, Card::Horsemen);
	std::fill(deck.begin()+14, deck.begin()+27, Card::Cannon);
	std::fill(deck.begin()+28, deck.begin()+41, Card::Soldier);
	deck.push_back(Card::Joker);
	deck.push_back(Card::Joker);

	std::random_shuffle(deck.begin(), deck.end());

	std::vector<Territory*> terrPtrs;
	for (Territory& terr : territories)
		terrPtrs.push_back(&terr);

	std::random_shuffle(terrPtrs.begin(), terrPtrs.end());

	for (int i = 0; i < numPlayers; i++) {
		//Just (human) user for now
		players.push_back(std::make_unique<User>("Player " + std::to_string(i + 1), static_cast<Color>(i)));
	}

	auto plr = players.begin();

	//Note: implement card land association later
	//See "The Setup" section of Risk booklet
	while (!terrPtrs.empty()) {
		Territory* terr = terrPtrs.back();
		terr->armies = 1;
		terr->owner = plr->get();

		(*plr)->terrs.push_back(terr);
		terrPtrs.pop_back();

		plr++;
		if (plr == players.end())
			plr = players.begin();
	}
};


//THIS is where the fun begins!
void Game::doTurn() {
	
	Player* plr = players[turnNum].get();

	plr->armies = std::max(plr->terrs.size() / 3, 3ul);
	turnState = TurnPhase::PlacingArmies;

	//Are they allowed to end their turn in this?
	do {

		std::unique_ptr<Command> cmd(plr->getCommand(*this));
		plr->commandError = !cmd->Execute(*this);
	} while (plr->armies > 0 && !plr->endTurn);
	plr->commandError = false;


	turnState = TurnPhase::FreeMove;

	do {

		std::unique_ptr<Command> cmd(plr->getCommand(*this));
		plr->commandError = !cmd->Execute(*this);
	} while (!plr->endTurn && plr->commandError);


	//Attack mode >:D	
	do {
		turnState = TurnPhase::AttackInit;

		std::unique_ptr<Command> cmd(plr->getCommand(*this));
		plr->commandError = !cmd->Execute(*this);

		if (plr->commandError) {
			continue;
		} else if (plr->endTurn) {
			break;
		}

		Player* targetPlr = attackState.target->owner;

		turnState = TurnPhase::DefendInit;
		do {
			std::unique_ptr<Command> cmd(targetPlr->getCommand(*this));
			targetPlr->commandError = !cmd->Execute(*this);

		} while (targetPlr->commandError);

		execAttack();

		attackState = { nullptr, nullptr, 0, 0 };
	} while (true);

	//End of turn code
	if (turnNum == players.size() - 1)
		turnNum = 0;
	else
		turnNum++;
	
}

/*Note: game rules force the territory a victor
was attacking from to become unoccupied if the victor
attacked with one more die than the attacking
territory, and lost one army during the battle; this
flaw was remedied in the implementation. Look into this 
more online.*/

void Game::execAttack() {
	std::vector<int> attackRolls;
	std::vector<int> defendRolls;

	int numBattles = std::min(attackState.attackDie, attackState.defendDie);

	for (int i = 0; i < numBattles; i++)
		attackRolls.push_back(rollDie());
	
	for (int i = 0; i < numBattles; i++)
		defendRolls.push_back(rollDie());


	for (int i = 0; i < numBattles; i++) {

		auto maxAtk = std::max_element(attackRolls.begin(),
				attackRolls.end());
		auto maxDf = std::max_element(defendRolls.begin(),
			defendRolls.end());

		if (*maxAtk > *maxDf) 
			attackState.target->armies--;
		else
			attackState.origin->armies--;


		/*
		//DEBUG----------------
		if (*maxAtk > *maxDf) {
			std::cout << attackState.target->owner->name;
		} else {
			std::cout << attackState.origin->owner->name;	
		}
		std::cout << " lost an army!" << std::endl;

		//---------------------
		*/
		attackRolls.erase(maxAtk);
		defendRolls.erase(maxDf);

	}

	/*
	std::cout << "Armies on " << attackState.origin->name <<
		": " << attackState.origin->armies << "\n";

	std::cout << "Armies on " << attackState.target->name <<
		": " << attackState.target->armies << std::endl;
	*/
	if (attackState.target->armies == 0) {
		turnState = TurnPhase::VictoryArmyMove;
		Player* victor = attackState.origin->owner;

		victor->terrs.push_back(attackState.target);

		std::vector<Territory*>& loserTerrs = attackState.target->owner->terrs;
		loserTerrs.erase(std::find(loserTerrs.begin(), loserTerrs.end(), attackState.target));

		attackState.target->owner = victor;

		if (attackState.origin->armies - attackState.attackDie > 1) {
			do {
				std::unique_ptr<Command> cmd(victor->getCommand(*this));
				cmd->Execute(*this);
			} while (victor->commandError);

		} else {
			attackState.target->armies += attackState.origin->armies - 1;
			attackState.origin->armies = 1;
		}

	}

}


//I KNOW IT'S GARBAGE PLS IGNORE IT I CAN EXPLAIN
std::vector<Territory> Game::genLandData() {
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

	for (auto cont : LandData::LandNames) {
		for (std::string terrName : cont.second) {
			territories.push_back(Territory(terrName, 
				contNameMap.at(cont.first)));
		}
	}

	for (int cont = LandData::data.size() - 1; cont >= 0; cont--) {
		for (int terr = LandData::data.at(cont).size() - 1; terr >= 0; terr--) {
			for (auto nbCord : LandData::data.at(cont).at(terr)) {

				territories.at(contNumOffs.at(cont)+terr).neighbors.push_back(&territories.at(contNumOffs.at(nbCord.first)+nbCord.second));
				territories.at(contNumOffs.at(nbCord.first)+nbCord.second).neighbors.push_back(&territories.at(contNumOffs.at(cont)+terr));
			}
		}
	}

	return territories;
}


int Game::rollDie() { 
	//TODO: use C++'s modern rand library
	return rand() % 6 + 1; 
}