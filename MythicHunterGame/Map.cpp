#include "Map.h"
#include "UtilFuncs.h"
#include <iostream>


#include "Potion.h"
#include "Magic.h"
#include "Armor.h"
#include "Weapon.h"

void Map::CheckSoftLocksInGeneration()
{
	if (map[0][1]->type  != "empty")
	{
		map[0][1]->ClearTile();
	}
	if (map[0][0]->type  != "empty")
	{
		map[0][0]->ClearTile();
	}
	if (map[1][0]->type  != "empty")
	{
		map[1][0]->ClearTile();
	}


	if (map[map_sizeY - 2][map_sizeX - 1]->type  != "empty")
	{
		map[map_sizeY - 2][map_sizeX - 1]->ClearTile();
	}
	if (map[map_sizeY-1][map_sizeX - 2]->type    != "empty")
	{
		map[map_sizeY-1][map_sizeX - 2]->ClearTile();
	}
	if (map[map_sizeY - 1][map_sizeX - 1]->type  != "empty")
	{
		map[map_sizeY - 1][map_sizeX - 1]->ClearTile();
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

Map::Tile::Tile(char _symbol, std::string _type) : symbol(_symbol), type(_type), pickUp(nullptr), monster(nullptr) {}

Map::Tile::Tile(char _symbol, std::string _type, Equipment* _pickUp) : symbol(_symbol), type(_type), pickUp(_pickUp), monster(nullptr) {}

Map::Tile::Tile(char _symbol, std::string _type, Monster* _monster) : symbol(_symbol), type(_type), pickUp(nullptr), monster(_monster) {}

const void Map::Tile::ClearTile()
{
	type = "empty";
	symbol = '.';
	pickUp = nullptr;
	monster = nullptr;
}

Map::Tile::~Tile()
{
	symbol = ' ';
	type = " ";
	if (pickUp != nullptr)
	{
		delete pickUp;
	}
	if (monster != nullptr)
	{
		delete monster;
	}
}

const bool Map::Tile::SaveData(std::ostream& out) const
{
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}


	out.write((const char*)&symbol, sizeof(symbol));

	size_t nameLength = type.size();
	out.write((const char*)&nameLength, sizeof(nameLength));
	out.write(type.c_str(), nameLength);

	bool hasMonster = monster != nullptr;
	out.write((const char*)&hasMonster, sizeof(hasMonster));
	if (hasMonster)
	{
		monster->SaveData(out);
	}

	bool hasPickUp = pickUp != nullptr;
	out.write((const char*)&hasPickUp, sizeof(hasPickUp));
	if (hasPickUp)
	{
		EquipmentType pickUpType = pickUp->GetType();
		out.write((const char*)&pickUpType, sizeof(pickUpType));
		pickUp->SaveData(out);
	}

	return true;
}

const bool Map::Tile::LoadData(std::istream& in)
{
	in.read((char*)&symbol, sizeof(symbol));

	size_t nameLength;
	in.read((char*)&nameLength, sizeof(nameLength));

	type.resize(nameLength);
	in.read((char*)&type[0], nameLength);


	bool hasMonster;
	in.read((char*)&hasMonster, sizeof(hasMonster));
	if (hasMonster)
	{
		monster = new Monster();
		monster->LoadData(in);
	}

	bool hasPickUp;
	in.read((char*)&hasPickUp, sizeof(hasPickUp));
	if (hasPickUp)
	{
		EquipmentType pickUpType;
		in.read((char*)&pickUpType, sizeof(pickUpType));
		switch (pickUpType)
		{
		case EquipmentType::Offensive:
			pickUp = new Weapon("");
			break;
		case EquipmentType::Defensive:
			pickUp = new Armor("");
			break;
		case EquipmentType::Spell:
			pickUp = new Magic("");
			break;
		case EquipmentType::Usable:
			pickUp = new Potion("");
			break;
		default:
			std::cerr << "Invalid pick up type" << '\n';
			return false;
		}

		pickUp->LoadData(in);
	}

	return true;
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
				map[i][j] = (new Tile('I', "pickUp", GenerateItem()));
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
}

Equipment* Map::GenerateItem() const
{
	int randomItem = randomNumberInt(0, 3);
	switch (randomItem)
	{
	case 0:
		return new Weapon("Sword");
	case 1:
		return new Armor("Armor");
	case 2:
		return new Magic("Lightning spell");
	case 3:
		return new Potion("Mana Potion");
	}

	return new Weapon("invalid");
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
		map[monsterX][monsterY]->monster = nullptr;
	}
}

const bool Map::PlayerPickUpItem(Hero* player, Tile* tile, std::string& output) const
{
	if (tile->pickUp != nullptr)
	{
		if (player->PickupNewItem(tile->pickUp))
		{
			output = tile->pickUp->PickUpNotification();
			return true;
		}
		else
		{
			output = "Inventory is full";
			return false;
		}
	}

	output = "invalid item in tile";

	return false;
}

const bool Map::SaveData(std::ostream& out) const
{
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	for (int i = 0; i < map_sizeX; i++)
	{
		for (int j = 0; j < map_sizeY; j++)
		{
			map[i][j]->SaveData(out);
		}
	}

	return true;
}

const bool Map::LoadData(std::istream& in)
{
	if (!in)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	map.clear(); 
	map.resize(map_sizeX);
	for (int i = 0; i < map_sizeX; i++)
	{
		map[i].resize(map_sizeY);
		for (int j = 0; j < map_sizeY; j++)
		{
			map[i][j] = new Tile(' ', "");
			map[i][j]->LoadData(in);
		}
	}

	return true;
}

bool Map::IsPositionObstructed(const int y, const int x) const
{
	if (map[y][x]->type == "empty" || map[y][x]->type == "pickUp" || map[y][x]->type == "monster")
	{
		return false;
	}
	return true;
}

void Map::MovePlayerUp(bool& hasEnemy, Monster*& monster, Hero* player, std::string& output)
{
	const int playerX = player->GetPositionX();
	const int playerY = player->GetPositionY();

	int newPosition = playerY - 1;
	if (playerY > 0 && !IsPositionObstructed(newPosition, playerX))
	{
		if (map[newPosition][playerX]->type == "pickUp")
		{
			if (PlayerPickUpItem(player, map[newPosition][playerX], output))
			{
				map[newPosition][playerX]->type = "empty";
				map[newPosition][playerX]->symbol = '.';
				map[newPosition][playerX]->pickUp = nullptr;
			}
		}
		else if (map[newPosition][playerX]->type == "monster")
		{
			hasEnemy = true;
			monster = map[newPosition][playerX]->monster;
		}

		player->MoveUp();
	}

}

void Map::MovePlayerDown(bool& hasEnemy, Monster*& monster, Hero* player, std::string& output)
{
	const int playerX = player->GetPositionX();
	const int playerY = player->GetPositionY();

	int newPosition = playerY + 1;
	if (playerY < (map_sizeY - 1) && !IsPositionObstructed(newPosition, playerX))
	{
		if (map[newPosition][playerX]->type == "pickUp")
		{
			if (PlayerPickUpItem(player, map[newPosition][playerX], output))
			{
				map[newPosition][playerX]->type = "empty";
				map[newPosition][playerX]->symbol = '.';
				map[newPosition][playerX]->pickUp = nullptr;
			}
		}
		else if (map[newPosition][playerX]->type == "monster")
		{
			hasEnemy = true;
			monster = map[newPosition][playerX]->monster;
		}

		player->MoveDown();
	}

}
void Map::MovePlayerLeft(bool& hasEnemy, Monster*& monster, Hero* player, std::string& output)
{
	const int playerX = player->GetPositionX();
	const int playerY = player->GetPositionY();

	int newPosition = playerX - 1;
	if (playerX > 0 && !IsPositionObstructed(playerY, newPosition))
	{
		if (map[playerY][newPosition]->type == "pickUp")
		{
			if (PlayerPickUpItem(player, map[playerY][newPosition], output))
			{
				map[playerY][newPosition]->type = "empty";
				map[playerY][newPosition]->symbol = '.';
				map[playerY][newPosition]->pickUp = nullptr;
			}
		}
		else if (map[playerY][newPosition]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY][newPosition]->monster;
		}

		player->MoveLeft();
	}

}
void Map::MovePlayerRight(bool& hasEnemy, Monster*& monster, Hero* player, std::string& output)
{
	int playerX = player->GetPositionX();
	int playerY = player->GetPositionY();

	int newPosition = playerX + 1;
	if (playerX < (map_sizeX - 1) && !IsPositionObstructed(playerY, newPosition))
	{
		if (map[playerY][newPosition]->type == "pickUp")
		{
			if (PlayerPickUpItem(player, map[playerY][newPosition], output))
			{
				map[playerY][newPosition]->type = "empty";
				map[playerY][newPosition]->symbol = '.';
				map[playerY][newPosition]->pickUp = nullptr;
			}
		}
		if (map[playerY][newPosition]->type == "monster")
		{
			hasEnemy = true;
			monster = map[playerY][newPosition]->monster;
		}

		player->MoveRight();
	}

}

const void Map::PrintMap(bool& isPlayerFinished, Hero* player) const
{
	int playerX = player->GetPositionX();
	int playerY = player->GetPositionY();

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
		isPlayerFinished = true;
		player->NextFloor();
	}
}