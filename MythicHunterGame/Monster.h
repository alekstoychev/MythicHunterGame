#pragma once

#include "Character.h"
#include "Hero.h"

class Hero;

class Monster : public Character
{
	int xpDrop;
	int goldDrop;

public:
	Monster();
	Monster(int _power, double _health, int _positionX, int _positionY, int _xpDrop = 5, int _goldDrop = 2);
	Monster(const Monster& other);
	virtual ~Monster();

	// Returns the enemy's taken damage
	double DealDamage(Character* enemy) override;
	double TakeDamage(double damageAmount) override;

	const bool IsAlive() const override;
	const void ShowStats(std::ostream& ostr) const override;

	const void GetPosition(int& outX, int& outY) const;

	const int GetXpDrop() const;
	const int GetGoldDrop() const;
};