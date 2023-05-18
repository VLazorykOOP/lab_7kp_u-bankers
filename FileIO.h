#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "BankSystem.h"

using namespace std;

void ReadClientsFromFile(const string &fileName, Bank &bank)
{
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        // Assuming the data in the file is formatted as:
        // ID, Name, Surname, Age, Address, Phone, Email, Money, Card Status, Password

        int id, age;
        string name, surname, address, phone, email, cardStatus, password, cardNumber;
        double money;

        stringstream ss(line);
        char comma;

        ss >> id >> comma >> ws;
        getline(ss, name, ',');
        getline(ss >> ws, surname, ',');
        ss >> age >> comma >> ws;
        getline(ss >> ws, address, ',');
        getline(ss >> ws, phone, ',');
        getline(ss >> ws, email, ',');
        ss >> money >> comma >> ws;
        getline(ss >> ws, cardNumber, ',');
        getline(ss >> ws, cardStatus, ',');
        getline(ss >> ws, password, ',');

        // Create a Client object using the extracted information
        Client client;
        client.SetId(id);
        client.SetName(name);
        client.SetSurname(surname);
        client.SetAge(age);
        client.SetAddress(address);
        client.SetPhone(phone);
        client.SetEmail(email);
        client.account.card.SetBalance(money);
        client.SetPassword(password);
        client.account.card.SetCardNumber(cardNumber);

        // Check if card status is "active"
        if (cardStatus == "active")
        {
            client.account.card.SetIsActive(true);
        }
        else
        {
            client.account.card.SetIsActive(false);
        }

        // Add the Client object to the Bank's clients vector
        bank.AddClient(client);
    }

    inputFile.close();
}

void ReadAdminsFromFile(const string &fileName, Bank &bank)
{
    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        // Assuming the data in the file is formatted as:
        // ID, Name, Surname, Address, Phone, Email, Password

        int id;
        string name, surname, address, phone, email, password;

        stringstream ss(line);
        char comma;

        ss >> id >> comma;
        getline(ss, name, ',');
        getline(ss, surname, ',');
        getline(ss, address, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');

        // Create an Admin object using the extracted information
        Admin admin;
        admin.SetId(id);
        admin.SetName(name);
        admin.SetSurname(surname);
        admin.SetAddress(address);
        admin.SetPhone(phone);
        admin.SetEmail(email);
        admin.SetPassword(password);

        // Add the Admin object to the Bank's admins vector
        bank.AddAdmin(admin);
    }

    inputFile.close();
}

void RewriteAdminsToFile(const string &fileName, vector<Admin> &admins)
{
    ofstream outputFile(fileName);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    for (auto &admin : admins)
    {
        // Write admin information to the file
        outputFile << admin.GetId() << ",";
        outputFile << admin.GetName() << ",";
        outputFile << admin.GetSurname() << ",";
        outputFile << admin.GetAddress() << ",";
        outputFile << admin.GetPhone() << ",";
        outputFile << admin.GetEmail() << ",";
        outputFile << admin.GetPassword() << endl;
    }

    outputFile.close();
}
void RewriteClientsToFile(const string &fileName, vector<Client> &clients)
{
    ofstream outputFile(fileName);
    if (!outputFile.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    for (auto &client : clients)
    {
        // Write client information to the file
        outputFile << client.GetId() << ", ";
        outputFile << client.GetName() << ", ";
        outputFile << client.GetSurname() << ", ";
        outputFile << client.GetAge() << ", ";
        outputFile << client.GetAddress() << ", ";
        outputFile << client.GetPhone() << ", ";
        outputFile << client.GetEmail() << ", ";
        outputFile << client.account.card.GetBalance() << ", ";
        outputFile << client.account.card.GetBalance() << ", ";

        // Write card status based on the isActive flag
        if (client.account.card.GetIsActive())
        {
            outputFile << "active, ";
        }
        else
        {
            outputFile << "inactive, ";
        }

        outputFile << client.GetPassword() << endl;

        // cout << "Client " << client.GetName() << " " << client.GetSurname() << " has been successfully written to the file." << endl;
    }

    outputFile.close();
}
