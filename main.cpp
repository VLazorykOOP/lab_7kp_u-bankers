#include <iostream>
#include <string>
#include <vector>
#include "BankSystem.h"
#include "menu.h"

int main()
{
    Bank bank;
    ReadClientsFromFile("clients.txt", bank);
    ReadAdminsFromFile("admins.txt", bank);

    int choice;
    // bank.PrintAllAdmins();
    MainMenu(choice, bank);

    return 0;
}