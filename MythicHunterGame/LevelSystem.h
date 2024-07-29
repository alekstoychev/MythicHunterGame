#pragma once

#include <fstream>

struct ListNode
{
	int requiredXP;
	int goldPrize;
	ListNode* next;

	ListNode(const int& _requiredXP, const int& _goldPrize, ListNode* _next = nullptr) : requiredXP(_requiredXP), goldPrize(_goldPrize), next(_next) {}

	static void pushFront(ListNode*& first, int requiredXP, int goldPrize);
	static void pushBack(ListNode*& first, int requiredXP, int goldPrize);
	static void pushAt(ListNode*& first, size_t index, int requiredXP, int goldPrize);
	static void popFront(ListNode*& first);
	static void popBack(ListNode*& first);
	static void popAt(ListNode*& first, size_t index);
	static void reverse(ListNode*& first);
	static bool checkForLoop(ListNode*& first);
	static ListNode*& find(ListNode*& first, int data);
	static void destroy(ListNode*& first);
};

struct LevelSystem
{
	static ListNode* GenerateXPRoad(int levels, double xpIncrease, double goldIncrease);
	static bool ValidateXPRoad(ListNode* xpRoad);
	static void ModifyXPRoadRewards(ListNode* xpRoad, int nthLv, double prizeBoost);
	static void UpdateLevel(ListNode*& currLevel, int playerXP, int& gold, std::string& message);
	static bool SaveXPRoad(ListNode* xpRoad, std::ostream& out);
	static bool LoadXPRoad(ListNode*& xpRoad, std::istream& in);
};