#pragma once

#include <vector>
#include <istream>

#include "Character.h"
#include "Monster.h"
#include "Equipment.h"
#include "Weapon.h"

const int inventory_size = 15;

class Monster;


class Hero : public Character
{
public:
	Hero(int _power, int _mana, double _health);
	~Hero();

	// Returns the enemy's taken damage
	double DealDamage(Character* enemy) override;
	double TakeDamage(double damageAmount) override;
	void Heal(double amount);

	const bool IsAlive() const override;
	const void ShowStats(std::ostream& ostr) const override;

	bool PickupNewItem(Equipment* newItem);
	bool ChangeEquippedWeapon(int index);
	bool ChangeEquippedArmor(int index);

	double SelectAndUseSpell(std::ostream& ostr, std::istream& istr, Character* enemy);
	double UsePotion(std::ostream& ostr, std::istream& istr);

	const void ShowInventory(std::ostream& ostr) const;
	const void ShowCurrentWeapon(std::ostream& ostr) const;
	const void ShowEquipped(std::ostream& ostr) const;


private:
	int mana;
	std::vector<Equipment*> inventory;
	Equipment* equippedSword;
	Equipment* equippedArmor;
};

