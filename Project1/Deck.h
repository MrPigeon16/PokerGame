#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "structs.h"
#include "Card.h"
using namespace std;


#define NUMBER_OF_CARDS 13
#define NUMBER_OF_SUIT 4

class Deck
{
public:
	Deck();
	void shuffle();
	Card draw();
	~Deck();

private:
	vector<Card> cards;

};