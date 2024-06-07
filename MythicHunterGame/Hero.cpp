#include "Hero.h"
#include "Magic.h"

Hero::Hero(int _power, int _mana, double _health, int _positionX, int _positionY) : Character(_power, _health, _positionX, _positionY), mana(_mana), equippedArmor(nullptr)
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

void Hero::Heal(double amount)
{
	health += amount;
}


// Returns true if it has space in the storage and has successfully added the item
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

double Hero::SelectAndUseSpell(std::ostream& ostr, std::istream& istr, Character* enemy)
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
	if (curSpellIdx == 0)
	{
		return 0.0;
	}

	int input;
	istr >> input;
	if (input > curSpellIdx || input < 1)
	{
		return 0.0;
	}

	input--;

	// downcasting
	// probably not the best idea
	Magic* selectedSpell = dynamic_cast<Magic*>(inventory[spellIndexes[input]]);

	// incase it failed to cast
	if (selectedSpell == nullptr)
	{
		return 0.0;
	}

	if (mana < selectedSpell->GetSpellCost())
	{
		ostr << "Not enough mana!" << '\n';
		return 0.0;
	}

	mana -= selectedSpell->GetSpellCost();

	return enemy->TakeDamage(inventory[spellIndexes[input]]->GetItemBonusStat());
}

double Hero::UsePotion(std::ostream& ostr, std::istream& istr)
{
	int spellIndexes[inventory_size] = { };
	int curSpellIdx = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->GetType() == EquipmentType::Usable)
		{
			ostr << curSpellIdx + 1 << ". ";
			inventory[i]->GetItemStats(ostr);
			ostr << '\n';

			spellIndexes[curSpellIdx] = i;
			curSpellIdx++;
		}
	}
	if (curSpellIdx == 0)
	{
		ostr << "You have no potions." << '\n';
		return 0.0;
	}

	int input;
	istr >> input;
	if (input > curSpellIdx || input < 1)
	{
		return 0.0;
	}

	input--;

	int manaRestore = inventory[spellIndexes[input]]->GetItemBonusStat();
	inventory.erase(inventory.begin() + spellIndexes[input]);
	mana += manaRestore;

	return manaRestore;
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

const bool Hero::IsInventoryFull() const
{
	if (inventory.size() >= inventory_size)
	{
		return true;
	}

	return false;
}

void Hero::MoveUp()
{
	positionY--;
}

void Hero::MoveDown()
{
	positionY++;
}

void Hero::MoveLeft()
{
	positionX--;
}

void Hero::MoveRight()
{
	positionX++;
}

void Hero::MoveToStart()
{
	positionX = 0;
	positionY = 0;
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
