#include "Armor.h"

Armor::Armor(std::string name) : Equipment(EquipmentType::Defensive, name), damageReduction(0)
{
	switch (rarity)
	{
	case Rarity::Common:
		damageReduction = randomNumberDouble(0.05, 0.10);
		break;
	case Rarity::Uncommon:
		damageReduction = randomNumberDouble(0.10, 0.25);
		break;
	case Rarity::Rare:
		damageReduction = randomNumberDouble(0.25, 0.30);
		break;
	case Rarity::Epic:
		damageReduction = randomNumberDouble(0.30, 0.35);
		break;
	case Rarity::Legendary:
		damageReduction = randomNumberDouble(0.35, 0.45);
		break;
	case Rarity::Mythic:
		damageReduction = randomNumberDouble(0.45, 0.50);
		break;
	}
}

const EquipmentType Armor::GetType() const
{
	return type;
}

Armor::~Armor()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	damageReduction = 0;
}


const void Armor::GetItemStats(std::ostream& ostr) const
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


	ostr << rarityStr << " " << name << " - " << damageReduction << " Armor";
}

const double Armor::GetItemBonusStat() const
{
	return damageReduction;
}
