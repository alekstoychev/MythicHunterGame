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

const double Equipment::GetItemBonusStat() const
{
	return bonusStat;
}

const std::string Equipment::PickUpNotification() const
{
	std::string output = "You picked up a ";

	switch (rarity)
	{
	case Rarity::Common:
		output += "common";
		break;
	case Rarity::Uncommon:
		output += "uncommon";
		break;
	case Rarity::Rare:
		output += "rare";
		break;
	case Rarity::Epic:
		output += "epic";
		break;
	case Rarity::Legendary:
		output += "legendary";
		break;
	case Rarity::Mythic:
		output += "mythic";
		break;
	}

	output += " " + name + "!";

	return output;
}

const bool Equipment::SaveData(std::ostream& out) const
{
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	size_t nameLength = name.size();
	out.write((const char*)&nameLength, sizeof(nameLength));
	out.write(name.c_str(), nameLength);

	out.write((const char*)&rarity, sizeof(rarity));
	out.write((const char*)&type, sizeof(type));
	out.write((const char*)&bonusStat, sizeof(bonusStat));

	return true;
}

const bool Equipment::LoadData(std::istream& in)
{
	if (!in)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	size_t nameLength;
	in.read((char*)&nameLength, sizeof(nameLength));

	name.resize(nameLength);
	in.read((char*)&name[0], nameLength);

	in.read((char*)&rarity, sizeof(rarity));
	in.read((char*)&type, sizeof(type));
	in.read((char*)&bonusStat, sizeof(bonusStat));

	return true;
}
