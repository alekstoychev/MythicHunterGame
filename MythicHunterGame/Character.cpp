#include "Character.h"

Character::Character(int _power, double _health) : power(_power), health(_health) {}

Character::Character(const Character& other)
{
	health = other.health;
	power = other.power;
}

Character::~Character()
{
	health = 0;
	power = 0;
}
