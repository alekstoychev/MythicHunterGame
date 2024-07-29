#pragma once
#include "Equipment.h"
#include "EnumTypes.h"

// For now the potion will only restore mana
class Potion : public Equipment
{
public:
	Potion(std::string name);
	virtual ~Potion();

	const Rarity GetRarity() const override;
	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;
};

