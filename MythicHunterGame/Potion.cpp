#include "Potion.h"

Potion::Potion(std::string name) : Equipment(EquipmentType::Usable, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		bonusStat = randomNumberInt(1, 5);
		break;
	case Rarity::Uncommon:
		bonusStat = randomNumberInt(5, 10);
		break;
	case Rarity::Rare:
		bonusStat = randomNumberInt(10, 15);
		break;
	case Rarity::Epic:
		bonusStat = randomNumberInt(15, 20);
		break;
	case Rarity::Legendary:
		bonusStat = randomNumberInt(20, 25);
		break;
	case Rarity::Mythic:
		bonusStat = randomNumberInt(25, 30);
		break;
	}
}

Potion::~Potion()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	bonusStat = 0;
}

const Rarity Potion::GetRarity() const
{
	return rarity;
}

const EquipmentType Potion::GetType() const
{
	return type;
}

const void Potion::GetItemStats(std::ostream& ostr) const
{
	std::string rarityStr;
	switch (rarity)
	{
	case Rarity::Common:
		rarityStr = "Common";
		break;
	case Rarity::Uncommon:
		rarityStr = "Uncommon";
		break;
	case Rarity::Rare:
		rarityStr = "Rare";
		break;
	case Rarity::Epic:
		rarityStr = "Epic";
		break;
	case Rarity::Legendary:
		rarityStr = "Legendary";
		break;
	case Rarity::Mythic:
		rarityStr = "Mythic";
		break;
	}

	ostr << rarityStr << " " << name << " [" << "Maga Restoration: " << bonusStat << "]";
}