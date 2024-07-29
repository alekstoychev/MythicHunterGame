#pragma once

#include <iostream>
#include <conio.h> // used for _getch()

#include "Hero.h"

struct InventoryManager
{
	static const void OpenInventory(Hero* player);
	static const void ChangeEquipped(Hero* player);
};

