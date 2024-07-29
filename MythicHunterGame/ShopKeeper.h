#pragma once

#include "Equipment.h"
#include <vector>
#include <functional>

#include "Hero.h"

class ShopKeeper
{
	std::vector<std::pair<Equipment*, int>> shop; // item and price with it

	int calculateItemPrice(Rarity rarity, int currentLevel);

public:
	ShopKeeper(int currentLevel);
	~ShopKeeper();

	void GenerateNewItems(int currentLevel);
	const void DisplayShop(std::ostream& out) const;

	int PurchaseItem(int idxChoice, int goldAmount, std::function<bool(Equipment*)> PickupNewItem);
};