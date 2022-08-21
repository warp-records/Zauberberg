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
