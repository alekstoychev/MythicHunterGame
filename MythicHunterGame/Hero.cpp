#include "Hero.h"
#include "Magic.h"

Hero::Hero(int _power, int _mana, double _health, int _positionX, int _positionY) : Character(_power, _health, _positionX, _positionY), mana(_mana), equippedArmor(nullptr)
{
	Weapon* newWeapon = new Weapon("Sword");

	inventory.reserve(inventory_size);
	inventory.push_back(newWeapon);

	equippedSword = newWeapon;
	currentFloor = 1;
	highestFloorReached = currentFloor;
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
	currentFloor = 0;
	highestFloorReached = 0;
	if (equippedArmor != nullptr)
	{
		delete equippedArmor;
	}
	if (equippedSword != nullptr)
	{
		delete equippedSword;
	}
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

const bool Hero::SaveData(std::ostream& out) const
{
	if (!Character::SaveData(out))
	{
		return false;
	}
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	out.write((const char*)&mana, sizeof(mana));

	size_t inventorySize = inventory.size();
	out.write((const char*)&inventorySize, sizeof(inventorySize));
	for (const auto& item : inventory)
	{
		EquipmentType type = item->GetType();
		out.write((const char*)&type, sizeof(type));
		item->SaveData(out);
	}

	bool isEquipped = equippedSword != nullptr;
	out.write((const char*)&isEquipped, sizeof(isEquipped));
	if (isEquipped)
	{
		EquipmentType type = equippedSword->GetType();
		out.write((const char*)&type, sizeof(type));
		equippedSword->SaveData(out);
	}

	isEquipped = equippedArmor != nullptr;
	out.write((const char*)&isEquipped, sizeof(isEquipped));
	if (isEquipped)
	{
		EquipmentType type = equippedArmor->GetType();
		out.write((const char*)&type, sizeof(type));
		equippedArmor->SaveData(out);
	}

	out.write((const char*)&currentFloor, sizeof(currentFloor));
	out.write((const char*)&highestFloorReached, sizeof(highestFloorReached));

	return true;
}

const bool Hero::LoadData(std::istream& in)
{
	if (!Character::LoadData(in))
	{
		return false;
	}
	if (!in)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}

	for (auto item : inventory)
	{
		delete item;
	}
	inventory.clear();
	equippedSword = nullptr;
	equippedArmor = nullptr;

	in.read((char*)&mana, sizeof(mana));
	
	size_t inventorySize;
	in.read((char*)&inventorySize, sizeof(inventorySize));
	if (inventorySize < 1)
	{
		return false;
	}
	inventory.resize(inventorySize);

	for (size_t i = 0; i < inventorySize; i++)
	{
		EquipmentType type;
		in.read((char*)&type, sizeof(type));
		switch (type)
		{
			case EquipmentType::Offensive:
				inventory[i] = new Weapon("Sword");
				break;
			case EquipmentType::Defensive:
				inventory[i] = new Armor("Armor");
				break;
			case EquipmentType::Spell:
				inventory[i] = new Magic("Lightning spell");
				break;
			case EquipmentType::Usable:
				inventory[i] = new Potion("Mana Potion");
				break;
		}
		if (inventory[i])
		{
			inventory[i]->LoadData(in);
		}
	}

	bool isEquipped;
	in.read((char*)&isEquipped, sizeof(isEquipped));
	if (isEquipped)
	{
		EquipmentType type;
		in.read((char*)&type, sizeof(type));
		equippedSword = new Weapon("Sword");
		equippedSword->LoadData(in);
	}

	in.read((char*)&isEquipped, sizeof(isEquipped));
	if (isEquipped)
	{
		EquipmentType type;
		in.read((char*)&type, sizeof(type));
		equippedArmor = new Armor("Armor");
		equippedArmor->LoadData(in);
	}

	in.read((char*)&currentFloor, sizeof(currentFloor));
	in.read((char*)&highestFloorReached, sizeof(highestFloorReached));

	return true;
}

const int Hero::GetCurrentFloor() const
{
	return currentFloor;
}

const int Hero::GetHighestFloorReached() const
{
	return highestFloorReached;
}

const void Hero::NextFloor()
{
	MoveToStart();
	currentFloor++;
	if (currentFloor > highestFloorReached)
	{
		highestFloorReached = currentFloor;
	}
}
