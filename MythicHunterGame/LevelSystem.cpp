#include "LevelSystem.h"

#include <iostream>
#include <conio.h> // used for _getch()

#include <string>


void ListNode::pushFront(ListNode*& first, int requiredXP, int goldPrize)
{
	ListNode* newNode = new ListNode(requiredXP, goldPrize, first);
	first = newNode;
}

void ListNode::pushBack(ListNode*& first, int requiredXP, int goldPrize)
{
	if (!first)
	{
		first = new ListNode(requiredXP, goldPrize, nullptr);
		return;
	}

	ListNode* curr = first;
	ListNode* newNode = new ListNode(requiredXP, goldPrize, nullptr);
	while (curr->next)
	{
		curr = curr->next;
	}
	curr->next = newNode;
}

void ListNode::pushAt(ListNode*& first, size_t index, int requiredXP, int goldPrize)
{
	if (index == 0)
	{
		pushFront(first, requiredXP, goldPrize);
		return;
	}

	if (!first || !first->next)
	{
		return;
	}

	ListNode* curr = first;
	for (size_t i = 0; i < index - 1; i++)
	{
		if (!curr)
		{
			std::cout << "Invalid index" << std::endl;
			return;
		}
		curr = curr->next;
	}

	ListNode* newNode = new ListNode(requiredXP, goldPrize, nullptr);
	ListNode* next = curr->next;
	curr->next = newNode;
	newNode->next = next;
}

void ListNode::popFront(ListNode*& first)
{
	if (!first)
	{
		return;
	}

	if (!first->next)
	{
		delete first;
		first = nullptr;
		return;
	}

	ListNode* newFirst = first->next;
	delete first;
	first = newFirst;
}

void ListNode::popBack(ListNode*& first)
{
	if (!first)
	{
		return;
	}

	if (!first->next)
	{
		delete first;
		first = nullptr;
		return;
	}

	ListNode* curr = first;
	while (curr->next->next)
	{
		curr = curr->next;
	}
	delete curr->next;
	curr->next = nullptr;
}

void ListNode::popAt(ListNode*& first, size_t index)
{
	if (index == 0)
	{
		popFront(first);
		return;
	}

	if (!first || !first->next)
	{
		return;
	}

	ListNode* curr = first;
	for (size_t i = 0; i < index - 1; i++)
	{
		if (!curr->next)
		{
			std::cout << "Invalid index" << std::endl;
			return;
		}
		curr = curr->next;
	}

	ListNode* next = curr->next->next;
	delete curr->next;
	curr->next = next;
}

ListNode*& ListNode::find(ListNode*& first, int data)
{
	ListNode* curr = first;
	while (curr)
	{
		if (curr->requiredXP == data)
		{
			return curr;
		}
		curr = curr->next;
	}
	std::cout << "Element not found. First element returned.\n";
	return first;
}

void ListNode::reverse(ListNode*& first)
{
	ListNode* current = first;
	ListNode* prev = nullptr;
	ListNode* next = nullptr;

	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	first = prev;
}

bool ListNode::checkForLoop(ListNode*& first)
{
	ListNode* fastIterator = first;
	ListNode* slowIterator = first;

	do
	{
		fastIterator = fastIterator->next->next;
		slowIterator = slowIterator->next;
		if (fastIterator == slowIterator)
		{
			return true;
		}
	} while (fastIterator && slowIterator);
}


void ListNode::destroy(ListNode*& first)
{
	while (first)
	{
		ListNode* next = first->next;
		delete first;
		first = next;
	}
}



ListNode* LevelSystem::GenerateXPRoad(int levels, double xpIncrease, double goldIncrease)
{
	if (levels < 1)
	{
		return nullptr;
	}

	bool isFirstIteration = true;
	ListNode* xpRoad = new ListNode(0, 0, nullptr);
	levels--;
	double lastXPMilestone = 10;
	double lastgoldReward = 5;

	while (levels)
	{
		if (isFirstIteration)
		{
			ListNode::pushBack(xpRoad, lastXPMilestone, lastgoldReward);
			isFirstIteration = false;
			levels--;
			continue;
		}

		lastXPMilestone += xpIncrease;
		lastgoldReward += goldIncrease;
		ListNode::pushBack(xpRoad, lastXPMilestone, lastgoldReward);
		levels--;
	}

	return xpRoad;
}

bool LevelSystem::ValidateXPRoad(ListNode* xpRoadNode)
{
	if (!xpRoadNode)
	{
		std::cout << "XP road not created\n";
		return false;
	}

	while (xpRoadNode->next)
	{
		if ((xpRoadNode->requiredXP >= xpRoadNode->next->requiredXP) || (xpRoadNode->goldPrize >= xpRoadNode->next->goldPrize))
		{
			return false;
		}
		xpRoadNode = xpRoadNode->next;
	}

	return true;
}

void LevelSystem::ModifyXPRoadRewards(ListNode* xpRoadNode, int nthLv, double prizeBoost)
{
	if (!xpRoadNode)
	{
		std::cout << "XP road not created\n";
		return;
	}

	int remainingLevels = nthLv - 1;
	while (xpRoadNode)
	{
		if (!remainingLevels)
		{
			remainingLevels = nthLv;
			xpRoadNode->goldPrize *= prizeBoost;
		}
		xpRoadNode = xpRoadNode->next;
		remainingLevels--;
	}
}

void LevelSystem::UpdateLevel(ListNode*& currLevel, int playerXP, int& gold, std::string& message)
{
	if (!currLevel)
	{
		return;
	}

	while (playerXP >= currLevel->requiredXP)
	{
		if (currLevel->requiredXP == 0)
		{
			currLevel = currLevel->next;
			continue;
		}

		if (!currLevel->next)
		{
			message = "Max level reached!\n";
			return;
		}

		currLevel = currLevel->next;
		message = "Level up! \nYou received " + std::to_string(currLevel->goldPrize) + " gold!\n";

		gold += currLevel->goldPrize;
	}
}

bool LevelSystem::SaveXPRoad(ListNode* xpRoad, std::ostream& out)
{
	if (!out)
	{
		std::cout << "Invalid file" << '\n';
		return false;
	}

	while (xpRoad->next)
	{
		int xp = xpRoad->requiredXP;
		out.write((const char*)&xp, sizeof(xp));
		int gold = xpRoad->goldPrize;
		out.write((const char*)&gold, sizeof(gold));

		xpRoad = xpRoad->next;
	}

	int end = -1;
	out.write((const char*)&end, sizeof(end));

	return true;
}

bool LevelSystem::LoadXPRoad(ListNode*& xpRoad, std::istream& in)
{
	if (!in)
	{
		std::cout << "Invalid file" << '\n';
		return false;
	}

	ListNode* first = nullptr;
	ListNode* last = nullptr;
	while (true)
	{
		int xp;
		in.read((char*)&xp, sizeof(xp));

		if (xp == -1) // -1 is the sign meaning the xp road has ended
		{
			break;;
		}

		int gold;
		in.read((char*)&gold, sizeof(gold));

		ListNode* newNode = new ListNode(xp, gold);
		if (first == nullptr)
		{
			first = newNode;
			last = newNode;
		}
		else
		{
			last->next = newNode;
			last = newNode;
		}
	}

	xpRoad = first;

	return true;
}
