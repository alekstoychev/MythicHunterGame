#include "Potion.h"

Potion::Potion(std::string name) : Equipment(EquipmentType::Usable, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		manaRestore = randomNumberInt(1, 5);
		break;
	case Rarity::Uncommon:
		manaRestore = randomNumberInt(5, 10);
		break;
	case Rarity::Rare:
		manaRestore = randomNumberInt(10, 15);
		break;
	case Rarity::Epic:
		manaRestore = randomNumberInt(15, 20);
		break;
	case Rarity::Legendary:
		manaRestore = randomNumberInt(20, 25);
		break;
	case Rarity::Mythic:
		manaRestore = randomNumberInt(25, 30);
		break;
	}
}

Potion::Potion(std::string name, std::ostream& ostr) : Equipment(EquipmentType::Usable, name)
{
	switch (rarity)
	{
	case Rarity::Common:
		ostr << "common";
		manaRestore = randomNumberInt(1, 5);
		break;
	case Rarity::Uncommon:
		ostr << "uncommon";
		manaRestore = randomNumberInt(5, 10);
		break;
	case Rarity::Rare:
		ostr << "rare";
		manaRestore = randomNumberInt(10, 15);
		break;
	case Rarity::Epic:
		ostr << "epic";
		manaRestore = randomNumberInt(15, 20);
		break;
	case Rarity::Legendary:
		ostr << "legendary";
		manaRestore = randomNumberInt(20, 25);
		break;
	case Rarity::Mythic:
		ostr << "mythic";
		manaRestore = randomNumberInt(25, 30);
		break;
	}

	ostr << " " << name << "!" << '\n';
}

Potion::~Potion()
{
	rarity = Rarity::Invalid;
	type = EquipmentType::Invalid;
	manaRestore = 0;
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

	ostr << rarityStr << name << '\n';
	ostr << "Maga Restoration: " << manaRestore << '\n';
}

const double Potion::GetItemBonusStat() const
{
	return manaRestore;
}
