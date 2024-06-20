#include "SaveGameSystem.h"

SaveGameSystem::SaveGameSystem() : playerFileName("player_data.dat"), mapFileName("map_data.dat") {}

const bool SaveGameSystem::SaveGame(Character* player, Map* map)
{
	binary.open(playerFileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!binary.is_open())
	{
		std::cerr << "Couldn't open file" << playerFileName << '\n';
		return false;
	}

	player->SaveData(binary);

	if (!binary)
	{
		std::cerr << "Error saving to file" << playerFileName << '\n';
		return false;
	}

	binary.close();



	binary.open(mapFileName, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!binary.is_open())
	{
		std::cerr << "Couldn't open file" << mapFileName << '\n';
		return false;
	}

	map->SaveData(binary);

	if (!binary)
	{
		std::cerr << "Error saving to file" << mapFileName << '\n';
		return false;
	}

	binary.close();


	return true;
}

const bool SaveGameSystem::LoadGame(Character* player, Map* map)
{
	binary.open(playerFileName, std::ios::binary | std::ios::in);
	if (!binary.is_open())
	{
		std::cerr << "Couldn't open file " << playerFileName << '\n';
		return false;
	}

	player->LoadData(binary);

	if (!binary)
	{
		std::cerr << "Error reading from file " << playerFileName << '\n';
		return false;
	}

	binary.close();

	binary.open(mapFileName, std::ios::binary | std::ios::in);
	if (!binary.is_open())
	{
		std::cerr << "Couldn't open file " << mapFileName << '\n';
		return false;
	}

	map->LoadData(binary);

	if (!binary)
	{
		std::cerr << "Error reading from file " << mapFileName << '\n';
		return false;
	}

	binary.close();


	return true;
}

const bool SaveGameSystem::DoesSaveFileExist() const
{
	std::ifstream playerFile(playerFileName);
	std::ifstream mapFile(mapFileName);

	return playerFile.good() && mapFile.good();
}
