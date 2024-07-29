#include "InventoryManager.h"

const void InventoryManager::OpenInventory(Hero* player)
{
    int input;

    system("cls");
    std::ios::fixed;
    std::cout.precision(2);
    player->ShowInventory(std::cout);

    std::cout << '\n' << "Currently equipped:" << '\n';
    player->ShowEquipped(std::cout);

    while (true)
    {
        std::cout << '\n' << "Would you like to change anything?" << '\n';
        std::cout << "1. yes" << '\n';
        std::cout << "2. no" << '\n';
        std::cout << "Use the numbers" << '\n';

        std::cin >> input;
        if (input == 1)
        {
            ChangeEquipped(player);
        }
        else
        {
            break;
        }
    }
}

const void InventoryManager::ChangeEquipped(Hero* player)
{

    int input2;
    int input3;
    int input4;
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
