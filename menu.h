#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include "BankSystem.h"
#include "FileIO.h"

using namespace std;

Bank bank;
string AdminPassword = "";
string ClientPassword = "";

int adminId = 0, clientId = 0;

Admin admin;
Client client;

void AdminMenu(int &choice, Bank &bank, Admin &admin);
void ClientMenu(int &choice, Bank &bank, Client &client);

void MainMenu(int &choice, Bank &bank)
{

    do
    {
        cout << "=================================================================================" << endl;
        cout << "1. Login as an admin" << endl;
        cout << "2. Login as a client" << endl;
        cout << "3. Exit" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;

        cin >> choice;
        cout << "=================================================================================" << endl;

        switch (choice)
        {
        case 1:
            // AdminMenu(choice, bank, admin);
            cout << "Enter your ID: ";
            cin >> adminId;
            admin = bank.GetAdminById(adminId);

            if (admin.GetId() != 0)
            {
                // admin.SetPassword("admin");
                cout << "Enter your password: ";
                cin >> AdminPassword;
                if (admin.Login(AdminPassword))
                    AdminMenu(choice, bank, admin);
            }
            else
            {
                cout << "Invalid admin ID" << endl;
            }
            break;
        case 2:
            cout << "Enter your ID: ";
            cin >> clientId;
            client = bank.GetClientById(clientId);

            if (client.GetId() != 0)
            {
                // client.SetPassword("client");
                cout << "Enter your password: ";
                cin >> ClientPassword;
                if (client.Login(ClientPassword))
                    ClientMenu(choice, bank, client);
            }
            else
            {
                cout << "Invalid client ID" << endl;
            }
            break;
        case 3:
            break;
        default:
            cout << "Wrong choice" << endl;
            break;
        }

    } while (choice != 3);
}

void ClientMenu(int &choice, Bank &bank, Client &client)
{
    Client recipient;
    bool logout = false;
    // client = bank.GetClientById(clientId);
    do
    {
        cout << "=================================================================================" << endl;
        cout << "1. Show info about your account" << endl;
        cout << "2. Show info about your card" << endl;
        cout << "3. Buy something" << endl;
        cout << "4. Transfer money" << endl;
        cout << "5. Logout" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cin >> choice;
        cout << "---------------------------------------------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            // client.Print();
            client.account.Print();
            break;
        case 2:
            client.account.card.Print();
            break;
        case 3:
            double price;
            cout << "Enter the price: ";
            cin >> price;
            client.account.card.Purchase(price);
            cout << "Your balance after purchase: " << client.account.card.GetBalance() << endl;
            bank.UpdateClient(client);
            // client.Print();
            // bank.PrintAllClients();
            break;
        case 4:
        {
            double transfer;
            cout << "Enter the amount of money you want to transfer: ";
            cin >> transfer;
            int recipientId;
            cout << "Enter the ID of the recipient: ";
            cin >> recipientId;

            recipient = bank.GetClientById(recipientId);
            // cout << "Recipient info:" << endl;
            // recipient.Print();
            if (recipient.GetId() != 0)
            {
                // cout << "Recipient info:" << endl;
                // recipient.Print();
                client.account.Transfer(transfer, recipient.account);
                cout << "Updated account info:" << endl;
                client.account.Print();
                bank.UpdateClient(client);
                bank.UpdateClient(recipient);
            }
            else
            {
                cout << "Invalid recipient ID" << endl;
            }
        }
        break;
        case 5:
            logout = true;
            break;
        default:
            cout << "Wrong choice" << endl;
            break;
        }
    } while (!logout);

    // bank.PrintAllClients();
    RewriteClientsToFile("clients.txt", bank.GetClients());
    client.Logout();
}

void AdminMenu(int &choice, Bank &bank, Admin &admin)
{
    bool logout = false;
    int clientId;

    do
    {
        cout << "=================================================================================" << endl;
        cout << "1. Show all clients" << endl;
        cout << "2. Show info about a client" << endl;
        cout << "3. Delete a client" << endl;
        cout << "4. Cancel a client's card" << endl;
        cout << "5. Logout" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cin >> choice;
        cout << "---------------------------------------------------------------------------------" << endl;
        switch (choice)
        {
        case 1:
            bank.PrintAllClients();
            break;
        case 2:
            cout << "Enter the ID of the client: ";
            cin >> clientId;
            try
            {
                client = bank.GetClientById(clientId);
                client.Print();
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3:
            cout << "Enter the ID of the client you want to delete: ";
            cin >> clientId;
            try
            {
                client = bank.GetClientById(clientId);
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
            if (client.GetId() != 0)
            {
                bank.DeleteClient(client);
            }
            else
            {
                cout << "Invalid client ID" << endl;
            }

            break;
        case 4:
        {
            cout << "Enter the ID of the client: ";
            cin >> clientId;
            try
            {
                client = bank.GetClientById(clientId);
            }
            catch (const runtime_error &e)
            {
                cout << e.what() << endl;
            }
            if (client.GetId() != 0)
            {
                admin.CancelCard(client);
                bank.UpdateClient(client);
            }
            else
            {
                cout << "Invalid client ID" << endl;
            }
        }
        break;
        case 5:
            logout = true;
            break;
        default:
            cout << "Wrong choice" << endl;
            break;
        }
    } while (!logout);

    RewriteClientsToFile("clients.txt", bank.GetClients());
    RewriteAdminsToFile("admins.txt", bank.GetAdmins());
    admin.Logout();
}