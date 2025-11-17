#include "BetAction.h"

BetAction::BetAction(int amount)
	:amount(amount)
{
}

void BetAction::executeAction(Table& table, Player& player)
{

	if (!(player.bet(this->amount))) {
		throw "BetAction: player don't have enough funds";
	}
	
}
