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


void Player::resetHand() { this->hand.clear(); }


// Getters
int Player::getPlayerID() { return this->id; }

string Player::getPlayerUsername() { return this->username; }

int Player::getPlayerPostion() { return this->tablePosition; }

vector<Card> Player::getHandPlayerHnad() { return this->hand; }

PlayerState Player::getPlayerState() { return this->state; }




// Setters
void Player::setHand(vector<Card> cards) { this->hand = cards; }

void Player::setPlayerState(PlayerState s) { this->state = s; }




