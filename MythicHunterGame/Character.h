#pragma once

#include <ostream>

class Character
{
public:
	Character(int _power, double _health);
	Character(const Character& other);
	virtual ~Character();

	virtual double DealDamage(Character* enemy) = 0;
	virtual double TakeDamage(double damageAmount) = 0;

	const virtual bool IsAlive() const = 0;
	const virtual void ShowStats(std::ostream& ostr) const = 0;

protected:
	double health;
	int power;
};

