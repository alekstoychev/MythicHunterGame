#include "Weapon.h"

Weapon::Weapon(std::string name, std::ostream& ostr) : Equipment(EquipmentType::Offensive, name), bonusDamagePercent(0)
{
	switch (rarity)
	{
		case Rarity::Common:
			ostr << "common";
			bonusDamagePercent = randomNumberDouble(1.01, 1.10);
			break;
		case Rarity::Uncommon:
			ostr << "uncommon";
			bonusDamagePercent = randomNumberDouble(1.10, 1.20);
			break;
		case Rarity::Rare:
			ostr << "rare";
			bonusDamagePercent = randomNumberDouble(1.20, 1.30);
			break;
		case Rarity::Epic:
			ostr << "epic";
			bonusDamagePercent = randomNumberDouble(1.30, 1.40);
			break;
		case Rarity::Legendary:
			ostr << "legendary";
			bonusDamagePercent = randomNumberDouble(1.40, 1.50);
			break;
		case Rarity::Mythic:
			ostr << "mythic";
			bonusDamagePercent = randomNumberDouble(1.50, 1.60);
			break;
	}
	ostr << " " << name << "!" << '\n';
}

Weapon::Weapon(std::string name) : Equipment(EquipmentType::Offensive, name), bonusDamagePercent(0)
{
	switch (rarity)
	{
	case Rarity::Common:
		bonusDamagePercent = randomNumberDouble(1.01, 1.10);
		break;
	case Rarity::Uncommon:
		bonusDamagePercent = randomNumberDouble(1.10, 1.20);
		break;
	case Rarity::Rare:
		bonusDamagePercent = randomNumberDouble(1.20, 1.30);
		break;
	case Rarity::Epic:
		bonusDamagePercent = randomNumberDouble(1.30, 1.40);
		break;
	case Rarity::Legendary:
		bonusDamagePercent = randomNumberDouble(1.40, 1.50);
		break;
	case Rarity::Mythic:
		bonusDamagePercent = randomNumberDouble(1.50, 1.60);
		break;
	}
}

Weapon::~Weapon()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	bonusDamagePercent = 0;
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
	ostr << rarityStr << " " << name << " - " << bonusDamagePercent << " ATK %";
}

const double Weapon::GetItemBonusStat() const
{
	return bonusDamagePercent;
}
