

#include "land.hpp"
#include "player.hpp"
#include <array>

#pragma once

class Game {
	
	//This is gonna be a shitshow by the next commit
	std::array<Continent, 6> continents {{
		{"North America", { 	

			{"Alaska"}, 				//0 0
			{"Northwest Territory"}, 	//0 1
			{"Greenland"},				//0 2
			{"Alberta"},				//0 3
			{"Ontario"},				//0 4
			{"Quebec"},					//0 5
			{"Western United States"},	//0 6
			{"Eastern United States"},	//0 7
			{"Central America"}			//0 8
		}},

		{"South America", {		
			{"Venezuala"},				//1 0
			{"Peru"},					//1 1			
			{"Brazil"},					//1 2
			{"Argentina"}				//1 3
		}},

		{"Europe", {			
			{"Iceland"},				//2 0
			{"Scandanavia"},			//2 1
			{"Ukraine"},				//2 2
			{"Great Britain"},			//2 3		
			{"Northern Europe"},		//2 4
			{"Western Europe"},			//2 5
			{"Southern Europe"}			//2 6
		}},

		{"Africa", {			
			{"Egypt"},					//3 0
			{"North Africa"},			//3 1
			{"East Africa"},			//3 2
			{"Congo"},					//3 3
			{"South Africa"},			//3 4
			{"Madagasgar"}				//3 5
		}},

		{"Asia", {
			{"Ural"},					//4 0
			{"Siberia"},				//4 1
			{"Yaktusk"},				//4 2
			{"Kamchatka"},				//4 3
			{"Irkutsk"},				//4 4
			{"Mongolia"},				//4 5
			{"Japan"},					//4 6
			{"Afghanistam"},			//4 7
			{"China"},					//4 8
			{"Middle East"},			//4 9
			{"India"},					//4 10
			{"Siam"},					//4 11
		}},

		{"Australia", {
			{"Indonesia"},				//5 0
			{"New Guinea"},				//5 1
			{"Western Australia"},		//5 2
			{"Eastern Australia"},		//5 3
		}}
	}};



public:
	Game();	
};