#include "Weapon.h"

Weapon::Weapon(std::string name) : Equipment(EquipmentType::Offensive, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		bonusStat = randomNumberDouble(1.01, 1.10);
		break;
	case Rarity::Uncommon:
		bonusStat = randomNumberDouble(1.10, 1.20);
		break;
	case Rarity::Rare:
		bonusStat = randomNumberDouble(1.20, 1.30);
		break;
	case Rarity::Epic:
		bonusStat = randomNumberDouble(1.30, 1.40);
		break;
	case Rarity::Legendary:
		bonusStat = randomNumberDouble(1.40, 1.50);
		break;
	case Rarity::Mythic:
		bonusStat = randomNumberDouble(1.50, 1.60);
		break;
	}
}

Weapon::~Weapon()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	bonusStat = 0;
}

const EquipmentType Weapon::GetType() const
{
	return type;
}

const void Weapon::GetItemStats(std::ostream& ostr) const
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

	ostr << std::fixed << std::setprecision(2);
	ostr << rarityStr << " " << name << " - " << bonusStat << " ATK %";
}
