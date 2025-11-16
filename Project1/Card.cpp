#include "Card.h"

Card::Card(CardSuit s, CardRank r)
	:suit(s), rank(r)
{
}

CardSuit Card::getCardSuit() { return this->suit; }

CardRank Card::getCardRank() { return this->rank; }


