#include "Monster.h"

Monster::Monster() : Character(1, 1, 0, 0) {}

Monster::Monster(int _power, double _health, int _positionX, int _positionY) : Character(_power, _health, _positionX, _positionY) {}

Monster::Monster(const Monster& other) : Character(other) {}

Monster::~Monster()
{
	power = 0;
	health = 0;
}

double Monster::DealDamage(Character* enemy)
{
	if (enemy == nullptr)
	{
		return 0.0;
	}

	return enemy->TakeDamage(power);
}

double Monster::TakeDamage(double damageAmount)
{
	health -= damageAmount;
	if (health < 0)
	{
		health = 0;
	}
	return damageAmount;
}

const bool Monster::IsAlive() const
{
	if (health > 0)
	{
		return true;
	}

	return false;
}

const void Monster::ShowStats(std::ostream& ostr) const
{
	ostr << "Health: " << health << '\n';
	ostr << "Power: " << power << '\n';
}

const void Monster::GetPosition(int& outX, int& outY) const
{
	outX = positionX;
	outY = positionY;
}
