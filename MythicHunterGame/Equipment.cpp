#include "Equipment.h"
#include "UtilFuncs.h"

Equipment::Equipment(EquipmentType _type, std::string& _name) : type(_type), name(_name) 
{
	int randomRarity = randomNumberInt(0, 100);
	if (randomRarity > 50)
	{
		rarity = Rarity::Common;
	}
	else if (randomRarity > 25)
	{
		rarity = Rarity::Uncommon;
	}
	else if (randomRarity > 15)
	{
		rarity = Rarity::Rare;
	}
	else if (randomRarity > 10)
	{
		rarity = Rarity::Epic;
	}
	else if (randomRarity > 5)
	{
		rarity = Rarity::Legendary;
	}
	else
	{
		rarity = Rarity::Mythic;
	}
}

Equipment::~Equipment()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	name = std::string();
}
