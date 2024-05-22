#pragma once

#include <string>
#include <vector>
#include "Weapon.h"
#include "Monster.h"

const int map_sizeX = 6;
const int map_sizeY = 6;

class Map
{
public:
	Map();
	~Map();

	struct Tile
	{
		char symbol;
		std::string type;
		//Weapon* pickUp;

		Monster* monster;

		Tile(char _symbol, std::string type);
		//Tile(char _symbol, std::string type, Weapon* _pickUp);

		Tile(char _symbol, std::string type, Monster* _enemy);
		~Tile();
	};

	void MovePlayerUp(bool& hasPickUp, bool& hasEnemy, Monster*& monster);
	void MovePlayerDown(bool& hasPickUp, bool& hasEnemy, Monster*& monster);
	void MovePlayerLeft(bool& hasPickUp, bool& hasEnemy, Monster*& monster);
	void MovePlayerRight(bool& hasPickUp, bool& hasEnemy, Monster*& monster);

	const void PrintMap(bool& isPlayerFinished) const;

	void GenerateNewMap();

	void EnemyKilled(Monster* monster);

private:

	std::vector<std::vector<Map::Tile*>> map;
	int playerX;
	int playerY;

	bool IsPositionObstructed(const int y, const int x) const;
	void CheckSoftLocksInGeneration();
};

