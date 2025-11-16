#pragma once

#include <iostream>
#include <vector>
using namespace std;

enum CardSuit
{
	HEARTS,
	DIAMONDS,
	CLUBS,
	SPADES
};

enum CardRank
{
	TWO = 2,
	THREE,
	FOUR,
	GIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE
};

enum PlayerState {
	CONNECTED,
	IN_TABLE,
	PLAYING,
	FOLDED,
	ALL_IN,
	DISCONNECTED
};

enum TableState
{
	WAITING_FOR_PLAYERS,
	STARTING_HAND,
	FLOP,
	TURN,
	RIVER,
	SHOWDOWN
};


enum ActionType
{
	FOLD,
	CHECK,
	CALL,
	BET,
	RAISE

};
