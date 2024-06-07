#pragma once

#include <ostream>

class Character
{
public:
	Character(int _power, double _health, int _positionX, int _positionY);
	Character(const Character& other);
	virtual ~Character();

	virtual double DealDamage(Character* enemy) = 0;
	virtual double TakeDamage(double damageAmount) = 0;

	const virtual bool IsAlive() const = 0; // implement instead of pure virtual
	const virtual void ShowStats(std::ostream& ostr) const = 0;

	const virtual int GetPositionX() const;
	const virtual int GetPositionY() const;

protected:
	double health;
	int power;

	int positionX;
	int positionY;
};

