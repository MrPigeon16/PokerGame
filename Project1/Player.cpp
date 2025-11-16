#include "Player.h"

Player::Player(int id, string username, long chips, int TablePostion, PlayerState state)
	:id(id), username(username), chips(chips), hand(), tablePosition(TablePostion), state(state)
{
}

Player::~Player()
{
}

bool Player::bet(int amount)
{
	if (amount <= this->chips)
	{
		this->chips -= amount;
		return true;
	}
	return false;
}

void Player::fold()
{
	this->state = FOLDED;
}

int Player::getPlayerID() { return this->id; }

