#include "Magic.h"

Magic::Magic(std::string name) : Equipment(EquipmentType::Spell, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		damage = randomNumberInt(5, 9);
		spellCost = 5;
		break;
	case Rarity::Uncommon:
		damage = randomNumberInt(9, 11);
		spellCost = 10;
		break;
	case Rarity::Rare:
		damage = randomNumberInt(11, 14);
		spellCost = 15;
		break;
	case Rarity::Epic:
		damage = randomNumberInt(14, 16);
		spellCost = 20;
		break;
	case Rarity::Legendary:
		damage = randomNumberInt(16, 18);
		spellCost = 25;
		break;
	case Rarity::Mythic:
		damage = randomNumberInt(18, 20);
		spellCost = 30;
		break;
	}
}

Magic::Magic(std::string name, std::ostream& ostr) : Equipment(EquipmentType::Spell, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		ostr << "common";
		damage = randomNumberInt(5, 9);
		spellCost = 5;
		break;
	case Rarity::Uncommon:
		ostr << "uncommon";
		damage = randomNumberInt(9, 11);
		spellCost = 10;
		break;
	case Rarity::Rare:
		ostr << "rare";
		damage = randomNumberInt(11, 14);
		spellCost = 15;
		break;
	case Rarity::Epic:
		ostr << "epic";
		damage = randomNumberInt(14, 16);
		spellCost = 20;
		break;
	case Rarity::Legendary:
		ostr << "legendary";
		damage = randomNumberInt(16, 18);
		spellCost = 25;
		break;
	case Rarity::Mythic:
		ostr << "mythic";
		damage = randomNumberInt(18, 20);
		spellCost = 30;
		break;
	}

	ostr << " " << name << "!" << '\n';
}

Magic::~Magic()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	damage = 0;
}

const EquipmentType Magic::GetType() const
{
	return EquipmentType::Spell;
}

const void Magic::GetItemStats(std::ostream& ostr) const
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

	ostr << rarityStr << name << '\n';
	ostr << "Damage: " << damage << '\n';
	ostr << "Spell Cost: " << spellCost << '\n';
}

const double Magic::GetItemBonusStat() const
{
	return damage;
}
