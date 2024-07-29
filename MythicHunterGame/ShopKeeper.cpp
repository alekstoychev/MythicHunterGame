#include "ShopKeeper.h"

#include "UtilFuncs.h"

#include "Weapon.h"
#include "Armor.h"
#include "Magic.h"
#include "Potion.h"

int ShopKeeper::calculateItemPrice(Rarity rarity, int currentLevel)
{
	int price = INT_MAX;

	switch (rarity)
	{
	case Rarity::Common:
		price = currentLevel + randomNumberInt(1, 10);
		break;
	case Rarity::Uncommon:
		price = (currentLevel + randomNumberInt(1, 10)) * 1.10;
		break;
	case Rarity::Rare:
		price = (currentLevel + randomNumberInt(1, 10)) * 1.20;
		break;
	case Rarity::Epic:
		price = (currentLevel + randomNumberInt(1, 10)) * 1.30;
		break;
	case Rarity::Legendary:
		price = (currentLevel + randomNumberInt(1, 10)) * 1.40;
		break;
	case Rarity::Mythic:
		price = (currentLevel + randomNumberInt(1, 10)) * 1.50;
		break;
	}

	return price;
}

ShopKeeper::ShopKeeper(int currentLevel)
{
	GenerateNewItems(currentLevel);
}

ShopKeeper::~ShopKeeper()
{
	for (auto& item : shop)
	{
		delete item.first;
		item.second = 0;
	}
}

void ShopKeeper::GenerateNewItems(int currentLevel)
{
	shop.clear();
	shop.resize(4);

	for (auto& item : shop)
	{
		int randomItem = randomNumberInt(0, 3);

		switch (randomItem)
		{
		case 0:
			item.first = new Weapon("Sword");
			break;
		case 1:
			item.first = new Armor("Armor");
			break;
		case 2:
			item.first = new Magic("Lightning spell");
			break;
		case 3:
			item.first = new Potion("Mana potion");
			break;
		default:
			item.first = nullptr;
			break;
		}

		int price = calculateItemPrice(item.first->GetRarity(), currentLevel);

		item.second = price;
	}
}

const void ShopKeeper::DisplayShop(std::ostream& out) const
{
	for (int i = 0; i < shop.size(); i++)
	{
		if (!shop[i].first)
		{
			std::cout << i + 1 << ". Empty" << '\n';
			continue;
		}

		out << i + 1 << ". ";
		shop[i].first->GetItemStats(out);
		out << " - " << shop[i].second << " gold." << '\n';
	}

	out << shop.size() + 1 << ". Return \n";
}

int ShopKeeper::PurchaseItem(int idxChoice, int goldAmount, std::function<bool(Equipment*)> PickupNewItem)
{
	int price = 0;

	if (idxChoice < 0 || idxChoice > 4)
	{
		return price;
	}

	if (!shop[idxChoice].first || shop[idxChoice].second <= 0)
	{
		std::cout << "Invalid shop item \n";
		return price;
	}

	if (goldAmount < shop[idxChoice].second)
	{
		std::cout << "Not enough gold!" << '\n';
		return price;
	}



	if (PickupNewItem(shop[idxChoice].first))
	{
		price = shop[idxChoice].second;

		shop[idxChoice].first = nullptr;
		shop[idxChoice].second = 0;

		std::cout << "Successful purchase! \n";
	}
	else
	{
		return 0;
	}


	return price;
}
