#include <iostream>
#include <windows.h> // used for Sleep()

#include "Character.h"
#include "Hero.h"
#include "Monster.h"

#include "Weapon.h"
#include "Armor.h"
#include "Map.h"

#include "UtilFuncs.h"

#include <conio.h>


static void Combat(Hero* player, Monster* monster)
{
    system("cls");
    std::cout << "You have entered combat!" << '\n';
    double playerLostHP = 0;
    int continueButton;
    while (true)
    {
        std::cout << "Your stats:" << '\n';
        player->ShowStats(std::cout);
        std::cout << '\n';
        std::cout << "Enemy stats:" << '\n';
        monster->ShowStats(std::cout);
        std::cout << '\n';
        std::cout << "What would you like to do?" << '\n';
        std::cout << "1. Weapon attack" << '\n';
        std::cout << "2. Magic Spell" << '\n';
        std::cout << "3. Use item" << '\n';
        std::cout << "Use the numbers" << '\n';

        int input;
        std::cin >> input;
        switch (input)
        {
            case 1:
                std::cout << "Currently equipped weapon: ";
                player->ShowCurrentWeapon(std::cout);
                std::cout << '\n' << "You attacked and hit it for " << player->DealDamage(monster) << '\n';
                break;
            case 2:
                std::cout << "Select a spell to use: ";
                player->SelectAndUseSpell(std::cout, std::cin, monster);
                break;
            case 3:
                break;
        }

        if (!monster->IsAlive())
        {
            playerLostHP *= 0.5;
            std::cout << "You killed it!" << '\n';
            std::cout << "You recovered " << playerLostHP << " health." << '\n';
            player->Heal(playerLostHP);
            continueButton = _getch();
            return;
        }

        double damageTaken = monster->DealDamage(player);
        playerLostHP += damageTaken;
        std::cout << "The monster attacked and hit you for " << damageTaken << '\n';
        if (!player->IsAlive())
        {
            std::cout << "You died!" << '\n';        
            continueButton = _getch();
            return;
        }

        continueButton = _getch();
        system("cls");
    }
}

static void InventoryManager(Hero* player)
{
    int input;
    int input2;
    int input3;
    int input4;

    system("cls");
    std::ios::fixed;
    std::cout.precision(2);
    player->ShowInventory(std::cout);

    std::cout << '\n' << "Currently equipped:" << '\n';
    player->ShowEquipped(std::cout);

    std::cout << '\n' << "Would you like to change anything?" << '\n';
    std::cout << "1. yes" << '\n';
    std::cout << "2. no" << '\n';
    std::cout << "Use the numbers" << '\n';

    std::cin >> input;
    if (input == 1)
    {
        std::cout << "What would you like to change?" << '\n';
        std::cout << "1. Weapon" << '\n';
        std::cout << "2. Armor" << '\n';

        std::cin >> input2;
        if (input2 == 1)
        {
            std::cout << "Enter the number of the weapon you want to change with:" << '\n';

            std::cin >> input3;
            if (player->ChangeEquippedWeapon(input3 - 1))
            {
                std::cout << "Successful." << '\n';
            }
            else
            {
                std::cout << "Unsuccessful" << '\n';
            }
        }
        else if (input2 == 2)
        {
            std::cout << "Enter the number of the armor you want to change with" << '\n';

            std::cin >> input3;
            if (player->ChangeEquippedArmor(input3 - 1))
            {
                std::cout << "Successful." << '\n';
            }
            else
            {
                std::cout << "Unsuccessful" << '\n';
            }
        }
        
        input4 = _getch();
    }
}


int main()
{
    Hero* player = new Hero(10, 5, 20);
    Map* gameMap = new Map();

    bool isLevelComplete = false;
    bool hasPickUp = false;
    bool isPlayerDone = false;


    int currentFloor = 1;
    int highestFloor = 1;

    
    while (!isPlayerDone)
    {
        system("cls");
        gameMap->PrintMap(isLevelComplete);
        if (isLevelComplete)
        {
            isLevelComplete = false;
            currentFloor++;
            if (currentFloor > highestFloor)
            {
                highestFloor = currentFloor;
            }
            gameMap->GenerateNewMap();
            continue;
        }

        std::cout << '\n' << "Current Floor: " << currentFloor;
        std::cout << '\n' << "Highest reached floor: " << highestFloor << '\n';
        std::cout << '\n';
        std::cout << "Your stats:" << '\n';
        player->ShowStats(std::cout);

        if (hasPickUp)
        {
            std::cout << '\n';
            std::cout << "You have picked up a ";
            int randomItem = randomNumberInt(1, 2);
            switch (randomItem)
            {
            case 1:
                player->PickupNewItem(new Weapon("Sword", std::cout));
                break;
            case 2:
                player->PickupNewItem(new Armor("Armor", std::cout));
                break;
            }
            std::cout << '\n';
        }
        else
        {
            
            std::cout << '\n';
        }

        std::cout << "Next direction (wasd): ";


        char input = _getch();
        /*
        char input;
        std::cin >> input;
        */

        Monster* encounter = new Monster();
        hasPickUp = false;
        bool hasEnemy = false;
        switch (input)
        {
        case 'w':
            gameMap->MovePlayerUp(hasPickUp, hasEnemy, encounter);
            break;
        case 's':
            gameMap->MovePlayerDown(hasPickUp, hasEnemy, encounter);
            break;
        case 'a':
            gameMap->MovePlayerLeft(hasPickUp, hasEnemy, encounter);
            break;
        case 'd':
            gameMap->MovePlayerRight(hasPickUp, hasEnemy, encounter);
            break;
        case 'r':
            gameMap->GenerateNewMap();
            break;
        case 'i':
            InventoryManager(player);
            break;
        case 'q':
            isPlayerDone = true;
            break;
        default:
            std::cout << "Invalid input" << '\n';
        }

        if (hasEnemy)
        {
            Combat(player, encounter);
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