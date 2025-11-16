#pragma once
#include "structs.h"
class Card
{
public:
	Card(CardSuit s, CardRank r);

	CardSuit getCardSuit();
	CardRank getCardRank();

private:

	CardSuit suit;
	CardRank rank;

};