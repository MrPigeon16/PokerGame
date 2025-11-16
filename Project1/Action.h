#pragma once
#include "Table.h"
#include "Player.h"

class Action
{
public:
	virtual ~Action() = default;
	virtual void executeAction(Table& table, Player& player) = 0;

};