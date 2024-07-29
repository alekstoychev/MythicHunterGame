#pragma once
#include "Equipment.h"

class Magic : public Equipment
{
public:
	Magic(std::string name);
	virtual ~Magic();

	const Rarity GetRarity() const override;
	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;

	const double GetSpellCost() const;

	const virtual bool SaveData(std::ostream& out) const override;
	const virtual bool LoadData(std::istream& in) override;
private:
	int spellCost;
};

