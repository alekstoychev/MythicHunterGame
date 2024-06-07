#include "Character.h"

Character::Character(int _power, double _health, int _positionX, int _positionY) 
	: power(_power), health(_health), positionX(_positionX), positionY(_positionY) {}

Character::Character(const Character& other)
{
	health = other.health;
	power = other.power;
	positionX = other.positionX;
	positionY = other.positionY;
}

Character::~Character()
{
	health = 0;
	power = 0;
	positionX = -1;
	positionY = -1;
}

const int Character::GetPositionX() const
{
	return positionX;
}

const int Character::GetPositionY() const
{
	return positionY;
}
