#include <iostream>
#include "Vault.h"
#include "User.h"
#include "PasswordGenerator.h"
#include "PasswordChecker.h"
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;

auto lastActive = chrono::system_clock::now();

void inactivityMonitor() {
    while (true)
    {
        this_thread::sleep_for(5s);
        auto now = chrono::system_clock::now();
        auto duration = now - lastActive;
        if (duration > 24s)
        {
            cout << "Exit for inactivity\n";
            exit(0);
        }
    }
}

int main()
{
    thread(inactivityMonitor).detach();
    User user;
    int choice;

    cout << "1. Register\n2. Login\n";
    cin >> choice;
    lastActive = chrono::system_clock::now();

    bool success = false;

    if (choice == 1)
    {
        user.registerUser();
        cout << "You are now logged in.\n";
        success = true; // skip login
    }
    else if (choice == 2)
    {
        int attempts = 0;

        while (attempts < 3)
        {
            if (user.login())
            {
                success = true;
                break;
            }
            attempts++;
        }
    }

    if (!success)
    {
        cout << "Too many attempts. Exiting.\n";
        return 0;
    }

    Vault vault(user.getUsername());
    PasswordGenerator generator;
    PasswordChecker checker;

    while (true)
    {
        cout << "\n===== PASSWORD MANAGER =====\n";

        cout << "1. Add Password\n";
        cout << "2. Generate Password\n";
        cout << "3. Check Password Strength\n";
        cout << "4. View Passwords\n";
        cout << "5. Exit\n";

        cin >> choice;
        lastActive = chrono::system_clock::now();

        if (choice == 1)
        {
            string site, pass;

            cout << "Site: ";
            cin >> site;
            cin.ignore(1000, '\n');
            lastActive = chrono::system_clock::now();
            cout << "Password: ";
            getline(cin,pass);
            if(pass.empty()){
                cout<<"Invalid Password\n";
                continue;
            }
            lastActive = chrono::system_clock::now();
            vault.addPassword(site, pass);
        }

        else if (choice == 2)
        {
            int len;

            cout << "Length: ";
            cin >> len;
            lastActive = chrono::system_clock::now();

            string generated = generator.generate(len);

            cout << "Generated Password: " << generated << endl;
        }

        else if (choice == 3)
        {
            string pass;

            cout << "Enter Password: ";
            cin >> pass;
            lastActive = chrono::system_clock::now();
            cout << "Strength: "
                 << checker.checkStrength(pass)
                 << endl;
        }

        else if (choice == 4)
        {
            vault.viewPasswords();
        }

        else if (choice == 5)
        {
            break;
        }
    }
}