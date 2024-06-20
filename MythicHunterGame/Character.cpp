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

const bool Character::SaveData(std::ostream& out) const
{
	if (!out)
	{
		std::cerr << "Invalid file" << '\n';
		return false;
	}
	out.write((const char*)&health, sizeof(health));
	out.write((const char*)&power, sizeof(power));
	out.write((const char*)&positionX, sizeof(positionX));
	out.write((const char*)&positionY, sizeof(positionY));

	return true;
}

const bool Character::LoadData(std::istream& in)
{
	if (!in)
	{
		std::cerr << "invalid file" << '\n';
		return false;
	}

	in.read((char*)&health, sizeof(health));
	in.read((char*)&power, sizeof(power));
	in.read((char*)&positionX, sizeof(positionX));
	in.read((char*)&positionY, sizeof(positionY));

	return true;
}
