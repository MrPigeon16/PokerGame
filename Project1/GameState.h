#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "structs.h"
class GameState
{
public:
	int dealerPostion;
	int currentTurn;
	int pot;
	std::vector<Card> communityCards;
	enum Phase {PreFlop,Flop,Turn,River,ShowDown};

};