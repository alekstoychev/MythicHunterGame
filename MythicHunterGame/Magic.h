#pragma once
#include "Equipment.h"

class Magic : public Equipment
{
public:
	Magic(std::string name);
	virtual ~Magic();

	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;

	const double GetItemBonusStat() const override;
	const double GetSpellCost() const;
private:
	int damage;
	int spellCost;
};

