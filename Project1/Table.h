#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include "Card.h"
#include "structs.h"
using namespace std;



class Table
{
public:
	Table();
	void addPlayer(Player* p);
	void removePlayer(int playerID);
	void dealCards();
	void dealFlop();
	void dealTurn();
	void dealRiver();
	void applyAction(int playerID, ActionType , int amout);
	~Table();


private:
	int id;
	vector<Player*> players;
	Deck* deck;
	vector<Card> publicCards;
	int pot;
	int currentBet;
	int dealerIndex;
	int currentTurnIndex;
	TableState state;

};