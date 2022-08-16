
#include "card.hpp"
#include <algorithm>
#include <map>

std::string cardToStr(Card card) {
	std::string str;

	std::map<Card, std::string> map;

	switch (card) {
		case (Card::Horsemen): {
			str = "Horsemen";
			break;
		}

		case (Card::Cannon): {
			str = "Cannon";
			break;
		}

		case (Card::Soldier): {
			str = "Soldier";
			break;
		}

		case (Card::Joker): {
			str = "Joker";
			break;
		}

		default:
			throw std::exception();
	}

	return str;
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
	

	/*
	Card card;

	switch (str) {
		case ("Horsemen"): {
			card = Card::Horsemen;
			break;
		}

		case ("Cannon"): {
			card = Card::Cannon;
			break;

		}

		case ("Soldier"): {
			card = Card::Soldier;
			break;
		}

		case ("Joker"): {
			card = Card::Joker;
			break;
		}

		default:
			throw std::exception();
	}*/
}