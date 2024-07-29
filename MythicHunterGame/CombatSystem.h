#pragma once

#include <iostream>
#include <conio.h> // used for _getch()

#include "Hero.h"
#include "Monster.h"

struct CombatSystem
{
	static const void BeginCombat(Hero* player, Monster* monster, std::string& message);
};

