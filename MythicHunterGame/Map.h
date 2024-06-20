#pragma once

#include <string>
#include <vector>
#include "Equipment.h"
#include "Monster.h"
#include "Hero.h"

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
		Equipment* pickUp;
		Monster* monster;

		Tile(char _symbol, std::string _type);
		Tile(char _symbol, std::string _type, Equipment* _pickUp);
		Tile(char _symbol, std::string _type, Monster* _enemy);
		const void ClearTile();
		~Tile();

		const bool SaveData(std::ostream& out) const;
		const bool LoadData(std::istream& in);
	};

	void MovePlayerUp   (bool& hasEnemy, Monster*& monster, Hero* player, std::string& output);
	void MovePlayerDown (bool& hasEnemy, Monster*& monster, Hero* player, std::string& output);
	void MovePlayerLeft (bool& hasEnemy, Monster*& monster, Hero* player, std::string& output);
	void MovePlayerRight(bool& hasEnemy, Monster*& monster, Hero* player, std::string& output);

	const void PrintMap(bool& isPlayerFinished, Hero* player) const;

	void GenerateNewMap();

	void EnemyKilled(Monster* monster);
	const bool PlayerPickUpItem(Hero* player, Tile* tile, std::string& output) const;

	const bool SaveData(std::ostream& out) const;
	const bool LoadData(std::istream& in);

private:

	std::vector<std::vector<Map::Tile*>> map;

	bool IsPositionObstructed(const int y, const int x) const;
	void CheckSoftLocksInGeneration();

	Equipment* GenerateItem() const;
};

