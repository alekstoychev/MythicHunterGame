#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
public:
	Armor(std::string name);
	virtual ~Armor();

	const Rarity GetRarity() const override;
	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;
};