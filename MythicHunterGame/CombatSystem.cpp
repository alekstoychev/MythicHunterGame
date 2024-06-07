#include "CombatSystem.h"

const void CombatSystem::BeginCombat(Hero* player, Monster* monster) const
{
    system("cls");
    std::cout << "You have entered combat!" << '\n';
    double playerLostHP = 0;
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
            std::cout << "Select a spell to use: " << '\n';
            std::cout << "You attacked and hit it for " << player->SelectAndUseSpell(std::cout, std::cin, monster) << '\n';
            break;
        case 3:
            std::cout << "You used a mana potion and restored " << player->UsePotion(std::cout, std::cin) << '\n';
            _getch();
            system("cls");
            continue;
        }

        if (!monster->IsAlive())
        {
            playerLostHP *= 0.5;
            std::cout << "You killed it!" << '\n';
            std::cout << "You recovered " << playerLostHP << " health." << '\n';
            player->Heal(playerLostHP);
            _getch();
            return;
        }

        double damageTaken = monster->DealDamage(player);
        playerLostHP += damageTaken;
        std::cout << "The monster attacked and hit you for " << damageTaken << '\n';
        if (!player->IsAlive())
        {
            std::cout << "You died!" << '\n';
            _getch();
            return;
        }

        _getch();
        system("cls");
    }
}
