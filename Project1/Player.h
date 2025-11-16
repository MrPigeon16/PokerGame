#pragma once
#include <iostream>
#include <vector>
#include "structs.h"
#include "Card.h"
using namespace std;


class Player
{

public:
	Player(int id, string username, long chips, int TablePostion, PlayerState state);
	~Player();
	bool bet(int amount);
	void fold();
	int getPlayerID();
	string getPlayerUsername();
	void setHand(vector<Card> cards);
	void setPlayerState(PlayerState s);


	
private:
	void resetHand();
	int id;
	string username;
	long chips;
	vector<Card> hand;
	int tablePosition;
	PlayerState state;



};