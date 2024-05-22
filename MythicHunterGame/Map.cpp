#include "Map.h"
#include "UtilFuncs.h"
#include <iostream>

void Map::CheckSoftLocksInGeneration()
{
	if (map[0][1]->type  != "empty")
	{
		map[0][1]->type   = "empty";
		map[0][1]->symbol = '.';

	}
	if (map[0][0]->type  != "empty")
	{
		map[0][0]->type   = "empty";
		map[0][0]->symbol = '.';
	}
	if (map[1][0]->type  != "empty")
	{
		map[1][0]->type   = "empty";
		map[1][0]->symbol = '.';
	}


	if (map[map_sizeY - 2][map_sizeX - 1]->type  != "empty")
	{
		map[map_sizeY - 2][map_sizeX - 1]->type   = "empty";
		map[map_sizeY - 2][map_sizeX - 1]->symbol = '.';
	}
	if (map[map_sizeY-1][map_sizeX - 2]->type    != "empty")
	{
		map[map_sizeY-1][map_sizeX - 2]->type     = "empty";
		map[map_sizeY-1][map_sizeX - 2]->symbol   = '.';
	}
	if (map[map_sizeY - 1][map_sizeX - 1]->type  != "empty")
	{
		map[map_sizeY - 1][map_sizeX - 1]->type   = "empty";
		map[map_sizeY - 1][map_sizeX - 1]->symbol = '.';
	}
}

Map::Map()
{
	GenerateNewMap();
}

Map::~Map()
{
	for (int i = 0; i < map_sizeX; i++)
	{
		for (int j = 0; j < map_sizeY; j++)
		{
			delete map[i][j];
		}
		std::cout << '\n';
	}
}

Map::Tile::Tile(char _symbol, std::string _type) : symbol(_symbol), type(_type), monster(nullptr) {}

//Map::Tile::Tile(char _symbol, std::string _type, Weapon* _pickUp) : symbol(_symbol), type(_type), pickUp(_pickUp), monster(nullptr) {}

Map::Tile::Tile(char _symbol, std::string _type, Monster* _monster) : symbol(_symbol), type(_type), monster(_monster) {}

Map::Tile::~Tile()
{
	symbol = ' ';
	type = " ";
	//delete pickUp;
	//delete monster;
}

void Map::GenerateNewMap()
{
	map.resize(map_sizeX);
	for (int i = 0; i < map_sizeX; i++)
	{
		map[i].resize(map_sizeY);
		for (int j = 0; j < map_sizeY; j++)
		{
			int random = randomNumberInt(0, 100);
			if (random > 80)
			{
				map[i][j] = (new Tile('#', "wall"));
			}
			else if (random > 70)
			{
				map[i][j] = (new Tile('I', "pickUp"));
			}
			else if (random > 60)
			{
				map[i][j] = (new Tile('M', "monster", new Monster(2, 20, i, j)));
			}
			else
			{
				map[i][j] = (new Tile('.', "empty"));
			}
		}
	}

	CheckSoftLocksInGeneration();

	playerX = 0;
	playerY = 0;
}

void Map::EnemyKilled(Monster* monster)
{
	if (!monster->IsAlive())
	{
		int monsterX;
		int monsterY;
		monster->GetPosition(monsterX, monsterY);
		map[monsterX][monsterY]->type = "empty";
		map[monsterX][monsterY]->symbol = '.';
		delete map[monsterX][monsterY]->monster;
	}
}

bool Map::IsPositionObstructed(const int y, const int x) const
{
	if (map[y][x]->type == "empty" || map[y][x]->type == "pickUp" || map[y][x]->type == "monster")
	{
		return false;
	}
	return true;
}

void Map::MovePlayerUp(bool& hasPickUp, bool& hasEnemy, Monster*& monster)
{
	if (playerY > 0 && !IsPositionObstructed(playerY - 1, playerX))
	{
		if (map[playerY - 1][playerX]->type == "pickUp")
		{
			hasPickUp = true;
			map[playerY - 1][playerX]->type = "empty";
			map[playerY - 1][playerX]->symbol = '.';
		}
		else if (map[playerY - 1][playerX]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY - 1][playerX]->monster;
		}

		playerY--;
	}

}

void Map::MovePlayerDown(bool& hasPickUp, bool& hasEnemy, Monster*& monster)
{
	if (playerY < (map_sizeY - 1) && !IsPositionObstructed(playerY + 1, playerX))
	{
		if (map[playerY + 1][playerX]->type == "pickUp")
		{
			hasPickUp = true;
			map[playerY + 1][playerX]->type = "empty";
			map[playerY + 1][playerX]->symbol = '.';
		}
		else if (map[playerY + 1][playerX]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY + 1][playerX]->monster;
		}

		playerY++;
	}

}
void Map::MovePlayerLeft(bool& hasPickUp, bool& hasEnemy, Monster*& monster)
{
	if (playerX > 0 && !IsPositionObstructed(playerY, playerX - 1))
	{
		if (map[playerY][playerX - 1]->type == "pickUp")
		{
			hasPickUp = true;
			map[playerY][playerX - 1]->type = "empty";
			map[playerY][playerX - 1]->symbol = '.';
		}
		else if (map[playerY][playerX - 1]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY][playerX - 1]->monster;
		}

		playerX--;
	}

}
void Map::MovePlayerRight(bool& hasPickUp, bool& hasEnemy, Monster*& monster)
{
	if (playerX < (map_sizeX - 1) && !IsPositionObstructed(playerY, playerX + 1))
	{
		if (map[playerY][playerX + 1]->type == "pickUp")
		{
			hasPickUp = true;
			map[playerY][playerX + 1]->type = "empty";
			map[playerY][playerX + 1]->symbol = '.';
		}
		if (map[playerY][playerX + 1]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY][playerX + 1]->monster;
		}

		playerX++;
	}

}

const void Map::PrintMap(bool& isPlayerFinished) const
{
	for (int i = 0; i < map_sizeX; i++)
	{
		for (int j = 0; j < map_sizeY; j++)
		{
			if (i == playerY && j == playerX)
			{
				std::cout << "H ";
			}
			else
			{
				std::cout << map[i][j]->symbol << " ";
			}
		}
		std::cout << '\n';
	}

	if (playerX == map_sizeX - 1 && playerY == map_sizeY - 1)
	{
		std::cout << '\n' << "You Win!" << '\n';
		isPlayerFinished = true;
	}
}