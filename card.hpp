#include <string>

#pragma once

enum class Card {
	Horsemen,
	Cannon,
	Soldier,
	Joker
};

std::string cardToStr(Card card);
Card strToCard(std::string const& str);

/*
	if (card.size() > 0) {
		try {
			for (Card card : cards)
				out += cardToStr(card) + ",\n";
		} catch (...) {
			plr->commandError = true;

			return getCommand(game);
		}

		//Remove last comma and newline
		out.pop_back();
		out.pop_back();

	} else {
		out = "(None)";
	}

	out += "\n";

	std::cout << out << std::endl;
	std::array<Card, 3> chosenCards;

	std::string option;

	try {
		for (int i = 0; i < 3; i++) {
			std::cin >> option;
			chosenCards[i] = strToCard(option);
		}
	} catch (...) {

	}
	*/