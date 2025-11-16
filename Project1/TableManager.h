#pragma once
#include <iostream>
#include <map>
#include "structs.h"
#include "Table.h"

using namespace std;

class TableManager
{

public:
	int createTable(int maxPlayers);
	void deleteTable(int tableID);
	Table* getTable(int tableID);
	void joinTable(int playerID, int tableID);

private:
	map<int, Table> tables;

};