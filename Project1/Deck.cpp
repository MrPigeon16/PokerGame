#include "Deck.h"



Deck::Deck()
{
	// Creating a fixed deck, NOT a shuffled deck
	for (size_t i = HEARTS ; i < NUMBER_OF_SUIT; i++)
	{
		for (size_t j = TWO; j < NUMBER_OF_CARDS; j++)
		{
			this->cards.push_back(Card(static_cast<CardSuit>(i), static_cast<CardRank>(j)));
		}
	}

}

void Deck::shuffle()
{
	std::random_device rd;

	std::mt19937 g(rd());

	//Shuffling the deck
	std::shuffle(this->cards.begin(), this->cards.end(), g);

}

Card Deck::draw()
{
	// Get the first Card
	Card drawCard = this->cards.front();
	// Removes the first card from the deck
	this->cards.erase(this->cards.begin());
	return drawCard;
}

Deck::~Deck() {}
