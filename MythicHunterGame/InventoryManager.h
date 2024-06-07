#pragma once

#include <iostream>
#include <conio.h> // used for _getch()

#include "Hero.h"

struct InventoryManager
{
	const void OpenInventory(Hero* player) const;
	const void ChangeEquipped(Hero* player) const;
};

