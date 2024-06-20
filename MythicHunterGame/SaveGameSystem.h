#pragma once
#include <string>
#include <fstream>

#include "Character.h"
#include "Map.h"

struct SaveGameSystem
{
	const char* playerFileName;
	const char* mapFileName;
	std::fstream binary;
	
	SaveGameSystem();
	const bool SaveGame(Character* player, Map* map);
	const bool LoadGame(Character* player, Map* map);

	const bool DoesSaveFileExist() const;
};

