#include "Table.h"

Table::Table()
	:deck()
{
	// NOT DONE
	this->deck->shuffle();
}

void Table::addPlayer(Player* p)
{
	this->players.push_back(p);
}

void Table::removePlayer(int playerID)
{
	Player* p = nullptr;
	// Find the player with this ID
	try
	{
		for (auto& player : this->players)
		{
			if (player->getPlayerID() == playerID)
			{
				p = player;
			}
		}
		this->players.erase(std::remove(this->players.begin(), this->players.end(), p), this->players.end());
	}
	catch (...)
	{
		throw "removePlayer: No such player with this ID";
	}

}

void Table::dealCards()
{
	for (auto* player : this->players)
	{
		vector<Card> hand = { this->deck->draw(),this->deck->draw() };
		player->setHand(hand);
	}
}

Table::~Table()
{
	delete this->deck;
}
