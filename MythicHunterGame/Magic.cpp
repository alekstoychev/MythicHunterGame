#include "Magic.h"

Magic::Magic(std::string name) : Equipment(EquipmentType::Spell, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		bonusStat = randomNumberInt(5, 9);
		spellCost = 5;
		break;
	case Rarity::Uncommon:
		bonusStat = randomNumberInt(9, 11);
		spellCost = 10;
		break;
	case Rarity::Rare:
		bonusStat = randomNumberInt(11, 14);
		spellCost = 15;
		break;
	case Rarity::Epic:
		bonusStat = randomNumberInt(14, 16);
		spellCost = 20;
		break;
	case Rarity::Legendary:
		bonusStat = randomNumberInt(16, 18);
		spellCost = 25;
		break;
	case Rarity::Mythic:
		bonusStat = randomNumberInt(18, 20);
		spellCost = 30;
		break;
	}
}

Magic::~Magic()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	bonusStat = 0;
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

	ostr << rarityStr << " " << name << " [" << "Damage: " << bonusStat << ", Spell Cost: " << spellCost << "]";
}

const double Magic::GetSpellCost() const
{
	return spellCost;
}

const bool Magic::SaveData(std::ostream& out) const
{
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	out.write((const char*)&spellCost, sizeof(spellCost));

	return true;
}

const bool Magic::LoadData(std::istream& in)
{
	if (!in)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	in.read((char*)&spellCost, sizeof(spellCost));

	return true;
}
