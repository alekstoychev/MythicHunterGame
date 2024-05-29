#pragma once
#include "Equipment.h"
#include "EnumTypes.h"

// For now the potion will only restore mana
class Potion : public Equipment
{
public:
	Potion(std::string name);
	Potion(std::string name, std::ostream& ostr);
	~Potion();

	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;

	const double GetItemBonusStat() const override;
private:
	int manaRestore;
};

