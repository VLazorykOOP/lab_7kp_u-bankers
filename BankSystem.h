#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class Person
{
private:
    int id;
    string name;
    string surname;
    string address;
    string phone;
    string email;
    string password;

public:
    Person() : name("No name"), surname("No surname"), address("No address"), phone("No phone"), email("No email"), id(0), password("") {}

    void SetId(int id)
    {
        this->id = id;
    }
    int GetId()
    {
        return id;
    }
    void SetName(string name)
    {
        this->name = name;
    }
    string GetName()
    {
        return name;
    }
    void SetSurname(string surname)
    {
        this->surname = surname;
    }
    string GetSurname()
    {
        return surname;
    }
    void SetAddress(string address)
    {
        this->address = address;
    }
    string GetAddress()
    {
        return address;
    }
    void SetPhone(string phone)
    {
        this->phone = phone;
    }
    string GetPhone()
    {
        return phone;
    }
    void SetEmail(string email)
    {
        this->email = email;
    }
    string GetEmail()
    {
        return email;
    }
    void SetPassword(string password)
    {
        this->password = password;
    }
    string GetPassword()
    {
        return password;
    }
    bool Login(string password)
    {
        if (this->password == password)
        {
            cout << "Login successful" << endl;
            return true;
        }
        else
        {
            cout << "Wrong password" << endl;
            return false;
        }
    }
    void Logout()
    {
        cout << "Logout successful" << endl;
    }
    void Print()
    {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "Address: " << address << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "Password: " << password << endl;
    }
};

class Card
{
private:
    double balance;
    string cardNumber;
    bool isActive;
    string SetCardNumber()
    {
        string cardNumber = "5168";
        for (int i = 0; i < 12; i++)
        {
            cardNumber += to_string(rand() % 10);
        }
        return cardNumber;
    }

public:
    Card()
    {
        isActive = true;
        balance = 0;
        cardNumber = SetCardNumber();
    }
    void SetIsActive(bool isActive)
    {
        this->isActive = isActive;
    }
    bool GetIsActive()
    {
        return isActive;
    }
    void SetBalance(double balance)
    {
        this->balance = balance;
    }
    double GetBalance()
    {
        return balance;
    }
    void SetCardNumber(string cardNumber)
    {
        this->cardNumber = cardNumber;
    }
    string GetCardNumber()
    {
        return cardNumber;
    }
    void AddMoney(double money)
    {
        if (isActive)
        {
            balance += money;
        }
        else
        {
            cout << "Card is not active" << endl;
        }
    }
    void Purchase(double price)
    {
        if (isActive)
        {
            if (balance >= price)
            {
                balance -= price;
                cout << "Purchase successful" << endl;
            }
            else
            {
                cout << "Not enough money" << endl;
            }
        }
        else
        {
            cout << "Card is not active" << endl;
        }
    }
    void Print()
    {
        cout << "Card info:" << endl;
        if (isActive)
        {
            cout << "Card is active" << endl;
            cout << "Card number: " << cardNumber << endl;
            cout << "Card balance: " << balance << endl;
            cout << endl;
        }
        else
        {
            cout << "Card is not active" << endl;
            cout << endl;
        }
    }
};

class Account
{
private:
    bool isActive;

public:
    Card card;
    Account()
    {
        isActive = true;
    }
    void Transfer(double money, Account &recipientAccount)
    {
        if (isActive)
        {
            if (card.GetBalance() >= money)
            {
                card.SetBalance(card.GetBalance() - money);
                recipientAccount.card.AddMoney(money);
                cout << "Money transfered" << endl;
            }
            else
            {
                cout << "Not enough money" << endl;
            }
        }
        else
        {
            cout << "Account is not active" << endl;
        }
    }
    void Buy(double price, Card card)
    {
        if (isActive)
        {
            if (card.GetBalance() >= price)
            {
                if (price < 10000)
                {
                    card.SetBalance(card.GetBalance() - price);
                }
                else
                {
                    cout << "You're trying to use suspiciously large amount of money" << endl;
                    cout << "We must block your card" << endl;
                    card.SetIsActive(false);
                }
            }
            else
            {
                cout << "Not enough money" << endl;
            }
        }
        else
        {
            cout << "Account is not active" << endl;
        }
    }
    void SetIsActive(bool isActive)
    {
        this->isActive = isActive;
    }
    bool GetIsActive()
    {
        return isActive;
    }
    void Print()
    {
        cout << "Account info:" << endl;
        if (isActive)
        {
            cout << "Account is active" << endl;
            cout << "Account balance:" << card.GetBalance() << endl;
            cout << endl;
        }
        else
        {
            cout << "Account is not active" << endl;
            cout << endl;
        }
    }
};

class Client : public Person
{
private:
    int age;

public:
    Account account;
    void Print()
    {
        cout << "Client info:" << endl;
        Person::Print();
        cout << "Age: " << age << endl;
        cout << endl;
        account.Print();
        account.card.Print();
        cout << endl;
    }

    void SetAge(int age)
    {
        this->age = age;
    }
    int GetAge()
    {
        return age;
    }
};

class Admin : public Person
{
private:
    // string password;

public:
    void CancelCard(Client &client)
    {
        client.account.card.SetIsActive(false);
        cout << "Card canceled" << endl;
        client.account.card.Print();
        cout << endl;
    }
    void CancelAccount(Client &client)
    {
        client.account.SetIsActive(false);
        client.account.card.SetBalance(0);
        cout << "Account canceled" << endl;
        cout << endl;
    }
    void Print()
    {
        cout << "Admin info:" << endl;
        Person::Print();
        cout << endl;
    }
};

class Bank
{
private:
    vector<Client> clients;
    vector<Admin> admins;

public:
    void AddClient(Client &client)
    {
        clients.push_back(client);
    }

    void AddAdmin(Admin &admin)
    {
        admins.push_back(admin);
    }
    void DeleteClient(Client &client)
    {
        for (auto it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->GetId() == client.GetId())
            {
                clients.erase(it);
                cout << "Client deleted" << endl;
                return;
            }
        }
    }

    void PrintAllClients()
    {
        for (auto &client : clients)
        {
            client.Print();
        }
    }

    void PrintAllAdmins()
    {
        for (auto &admin : admins)
        {
            admin.Print();
        }
    }
    Client &GetClientById(int clientId)
    {
        for (auto &client : clients)
        {
            if (client.GetId() == clientId)
            {
                return client;
            }
        }
        throw runtime_error("Client not found");
    }
    Admin &GetAdminById(int adminId)
    {
        for (auto &admin : admins)
        {
            if (admin.GetId() == adminId)
            {
                return admin;
            }
        }
        throw runtime_error("Admin not found");
    }

    vector<Client> &GetClients()
    {
        return clients;
    }
    vector<Admin> &GetAdmins()
    {
        return admins;
    }
    void UpdateClient(Client &client)
    {
        for (auto &existingClient : clients)
        {
            if (existingClient.GetId() == client.GetId())
            {
                // cout << "Client found" << endl;
                // Update the client with the new information
                existingClient.SetName(client.GetName());
                existingClient.SetSurname(client.GetSurname());
                existingClient.SetAddress(client.GetAddress());
                existingClient.SetPhone(client.GetPhone());
                existingClient.SetEmail(client.GetEmail());
                existingClient.SetPassword(client.GetPassword());
                existingClient.SetAge(client.GetAge());
                existingClient.account.card.SetBalance(client.account.card.GetBalance());
                existingClient.account.card.SetIsActive(client.account.card.GetIsActive());
                existingClient.account.SetIsActive(client.account.GetIsActive());

                // cout << "Client updated" << endl;
                return;
            }
        }

        throw runtime_error("Client not found");
    }
};
