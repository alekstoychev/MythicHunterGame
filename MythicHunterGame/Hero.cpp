#include "Hero.h"

Hero::Hero(int _power, int _mana, double _health) : Character(_power, _health), mana(_mana), equippedArmor(nullptr)
{
	Weapon* newWeapon = new Weapon("Sword");

	inventory.reserve(inventory_size);
	inventory.push_back(newWeapon);

	equippedSword = newWeapon;
}

Hero::~Hero()
{
	if (inventory.size() != 0)
	{
		for (int i = 0; i < inventory.size(); i++)
		{
			delete inventory[i];
		}	
	}

	mana = 0;
	health = 0;
	power = 0;
}

double Hero::DealDamage(Character* enemy)
{
	if (enemy == nullptr)
	{
		return 0.0;
	}

	double totalDamage = power;

	if (equippedSword != nullptr)
	{
		totalDamage *= equippedSword->GetItemBonusStat();
	}

	return enemy->TakeDamage(totalDamage);
}

double Hero::TakeDamage(double damageAmount)
{
	double damageTaken = damageAmount;
	
	if (equippedArmor != nullptr)
	{
		damageTaken -= damageAmount * equippedArmor->GetItemBonusStat();
		if (damageTaken < 0)
		{
			damageTaken = 0;
		}
	}
	
	health -= damageTaken;
	if (health < 0)
	{
		health = 0;
	}

	return damageTaken;
}


bool Hero::PickupNewItem(Equipment* newItem)
{
	if (inventory.size() < inventory_size)
	{
		inventory.push_back(newItem);
		return true;
	}

	return false;
}

bool Hero::ChangeEquippedWeapon(int index)
{
	if (index < inventory.size())
	{
		if (inventory[index]->GetType() == EquipmentType::Offensive)
		{
			equippedSword = inventory[index];
			return true;
		}
	}

	return false;
}

bool Hero::ChangeEquippedArmor(int index)
{
	if (index < inventory.size())
	{
		if (inventory[index]->GetType() == EquipmentType::Defensive)
		{
			equippedArmor = inventory[index];
			return true;
		}
	}

	return false;
}

const double Hero::SelectAndUseSpell(std::ostream& ostr, std::istream& istr, Character* enemy) const
{
	int spellIndexes[inventory_size] = { };
	int curSpellIdx = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->GetType() == EquipmentType::Spell)
		{
			ostr << curSpellIdx + 1 << ". ";
			inventory[i]->GetItemStats(ostr);
			ostr << '\n';

			spellIndexes[curSpellIdx] = i;
			curSpellIdx++;
		}
	}

	int input;
	istr >> input;
	if (input >= curSpellIdx)
	{
		return 0.0;
	}

	return enemy->TakeDamage(inventory[spellIndexes[input]]->GetItemBonusStat());
}

const void Hero::ShowInventory(std::ostream& ostr) const
{
	for (int i = 0; i < inventory.size(); i++)
	{
		ostr << i+1 << ". ";
		inventory[i]->GetItemStats(ostr);
		ostr << '\n';
	}
}

const void Hero::ShowEquipped(std::ostream& ostr) const
{
	if (equippedSword != nullptr)
	{
		equippedSword->GetItemStats(ostr);
		ostr << '\n';
	}

	if (equippedArmor != nullptr)
	{
		equippedArmor->GetItemStats(ostr);
		ostr << '\n';
	}
}

const void Hero::ShowCurrentWeapon(std::ostream& ostr) const
{
	equippedSword->GetItemStats(ostr);
}

const bool Hero::IsAlive() const
{
	if (health > 0)
	{
		return true;
	}

	return false;
}

const void Hero::ShowStats(std::ostream& ostr) const
{
	ostr << "Health: " << health << '\n';
	ostr << "Power: " << power << '\n';
	ostr << "Mana: " << mana << '\n';
}
