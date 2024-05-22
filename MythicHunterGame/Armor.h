#pragma once

#include "Equipment.h"

class Armor : public Equipment
{
public:
	Armor(std::string name);
	Armor(std::string name, std::ostream& ostr);
	~Armor();

	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;

	const double GetItemBonusStat() const override;

private:
	double damageReduction;
};