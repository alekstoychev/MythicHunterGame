#pragma once

#include <string>
#include <iomanip>
#include <ostream>
#include "EnumTypes.h"
#include "UtilFuncs.h"

class Equipment
{
public:
	Equipment(EquipmentType _type, std::string& _name);
	virtual ~Equipment();

	const virtual EquipmentType GetType() const = 0;
	const virtual void GetItemStats(std::ostream& ostr) const = 0;

	const virtual double GetItemBonusStat() const = 0;

protected:
	std::string name;
	Rarity rarity;
	EquipmentType type;
};

