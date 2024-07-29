#pragma once

#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "EnumTypes.h"
#include "UtilFuncs.h"

class Equipment
{
public:
	Equipment(EquipmentType _type, std::string& _name);
	virtual ~Equipment();

	const virtual Rarity GetRarity() const = 0;
	const virtual EquipmentType GetType() const = 0;
	const virtual void GetItemStats(std::ostream& ostr) const = 0;

	const virtual double GetItemBonusStat() const;

	const virtual std::string PickUpNotification() const;

	const virtual bool SaveData(std::ostream& out) const;
	const virtual bool LoadData(std::istream& in);

protected:
	std::string name;
	Rarity rarity;
	EquipmentType type;

	double bonusStat;
};

