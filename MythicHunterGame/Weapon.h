#pragma once

#include "Equipment.h"

class Weapon : public Equipment
{
public:
	Weapon(std::string name);
	virtual ~Weapon();

	const EquipmentType GetType() const override;
	const void GetItemStats(std::ostream& ostr) const override;
};
