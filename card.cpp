
#include "card.hpp"
#include <algorithm>
#include <map>

std::string cardToStr(Card card) {

	std::map<Card, std::string> map {
		{Card::Horsemen, "Horsemen"},
		{Card::Cannon, "Cannon"},
		{Card::Soldier, "Soldier"},
		{Card::Joker, "Joker"}
	};

	auto strItr = map.find(card);

	if (strItr == map.end())
		throw std::exception();

	return strItr->second;
}


Card strToCard(std::string const& str) {
	
	std::map<std::string, Card> map {
		{"Horsemen", Card::Horsemen},
		{"Cannon", Card::Cannon},
		{"Soldier", Card::Soldier},
		{"Joker", Card::Joker}
	};

	auto cardItr = map.find(str);

	if (cardItr == map.end())
		throw std::exception();

	return cardItr->second;
	
}