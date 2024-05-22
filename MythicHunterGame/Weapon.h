#pragma once

#include "Equipment.h"

class Weapon : public Equipment
{
public:
	Weapon(std::string name);
	Weapon(std::string name, std::ostream& ostr);
	~Weapon();

	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;

	const double GetItemBonusStat() const override;

private:
	double bonusDamagePercent;
};
