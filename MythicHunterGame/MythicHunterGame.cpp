#include <iostream>
#include <conio.h> // used for _getch()

#include "Hero.h"
#include "Monster.h"

#include "Weapon.h"
#include "Armor.h"
#include "Magic.h"
#include "Potion.h"

#include "CombatSystem.h"
#include "InventoryManager.h"
#include "SaveGameSystem.h"

#include "Map.h"

#include "UtilFuncs.h"

const char* game_version = "1.5.0";

const static void WelcomeScreen()
{
    system("cls");
    std::cout << "Welcome to Mythic Hunter " << game_version << '\n';
    std::cout << '\n' << "Controls are: " << '\n';
    std::cout << "W A S D - moving around" << '\n';
    std::cout << "I - open inventory" << '\n';
    std::cout << "R - reset map" << '\n';
    std::cout << "Q - quit game" << '\n';
    std::cout << '\n' << '\n' << "Use quit game feature so it saves!!!" << '\n';
    _getch();
    system("cls");
}

int main()
{
    Hero* player = new Hero(10, 5, 20, 0, 0);
    Map* gameMap = new Map();
    InventoryManager* inventoryManager = new InventoryManager();
    CombatSystem* combatSystem = new CombatSystem();
    SaveGameSystem* saveGameSystem = new SaveGameSystem();

    bool isLevelComplete = false;
    bool isPlayerDone = false;

    std::string pickUpMessage;

    WelcomeScreen();
    if (saveGameSystem->DoesSaveFileExist())
    {
        std::cout << "Would you like to continue from your save file or start a new game?" << '\n';
        std::cout << "1 - yes" << '\n';
        std::cout << "2 - no" << '\n';
        int input;
        std::cin >> input;
        if (input == 1)
        {
            saveGameSystem->LoadGame(player, gameMap);
        }
    }
    
    while (!isPlayerDone)
    {
        system("cls");
        gameMap->PrintMap(isLevelComplete, player);
        if (isLevelComplete)
        {
            isLevelComplete = false;
            gameMap->GenerateNewMap();
            continue;
        }

        std::cout << '\n' << "Current Floor: " << player->GetCurrentFloor();
        std::cout << '\n' << "Highest reached floor: " << player->GetHighestFloorReached() << '\n';
        std::cout << '\n';
        std::cout << "Your stats:" << '\n';
        player->ShowStats(std::cout);
        std::cout << '\n';

        if (!pickUpMessage.empty())
        {
            std::cout << pickUpMessage << '\n';
            std::cout << '\n';
            pickUpMessage.clear();
        }
        std::cout << "Next action (wasd, r, i, q): ";

        char input = _getch();
        /*
        char input;
        std::cin >> input;
        */

        Monster* encounter = new Monster();
        bool hasEnemy = false;

        switch (input)
        {
        case 'w':
            gameMap->MovePlayerUp(hasEnemy, encounter, player, pickUpMessage);
            break;
        case 's':
            gameMap->MovePlayerDown(hasEnemy, encounter, player, pickUpMessage);
            break;
        case 'a':
            gameMap->MovePlayerLeft(hasEnemy, encounter, player, pickUpMessage);
            break;
        case 'd':
            gameMap->MovePlayerRight(hasEnemy, encounter, player, pickUpMessage);
            break;
        case 'r':
            gameMap->GenerateNewMap();
            break;
        case 'i':
            inventoryManager->OpenInventory(player);
            break;
        case 'q':
            isPlayerDone = true;
            saveGameSystem->SaveGame(player, gameMap);
            break;
        default:
            std::cout << "Invalid input" << '\n';
        }

        if (hasEnemy)
        {
            combatSystem->BeginCombat(player, encounter);
            if (!player->IsAlive())
            {
                isPlayerDone = true;
            }
            else if (!encounter->IsAlive())
            {
                gameMap->EnemyKilled(encounter);
            }
        }
        else
        {
            delete encounter;
        }
    }


    delete player;
    delete gameMap;
}