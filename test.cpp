#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "BankSystem.h"
#include "FileIO.h"

using namespace std;

int main()
{
    Bank bank;
    vector<Client> clients;
    Client client;
    Admin admin;
    // vector<Client> clients;
    ReadClientsFromFile("clients.txt", bank);
    ReadAdminsFromFile("admins.txt", bank);
    clients = bank.GetClients();

    client = bank.GetClientById(1);
    // client.Print();
    admin = bank.GetAdminById(1);

    bank.DeleteClient(client);
    bank.PrintAllClients();

        // admin.CancelCard(client);
    // client.Print();

    return 0;
}