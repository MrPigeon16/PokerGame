#pragma once
#include "Action.h"
class BetAction : public Action
{
public:
	BetAction(int amount);
	void executeAction(Table& table, Player& player) override;

private:
	int amount;


};