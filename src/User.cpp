#include <iostream>
#include <fstream>
#include <conio.h>
#include "User.h"

using namespace std;


bool User::registerUser() {
    cout << "Enter username: ";
    cin >> username;
    
    cout << "Enter password: ";
    password = getPassword();
    
    ofstream file("data/users.txt", ios::app);
    file << username << " " << password << endl;
    
    cout << "User registered successfully!\n";
    return true;
}

bool User::login() {
    string inputUser, inputPass;
    
    cout << "Username: ";
    cin >> inputUser;
    
    cout << "Password: ";
    inputPass = getPassword();
    
    ifstream file("data/users.txt");
    string fileUser, filePass;
    
    while (file >> fileUser >> filePass) {
        if (fileUser == inputUser && filePass == inputPass) {
            username = inputUser; // 👈 STORE IT
            cout << "Login successful!\n";
            return true;
        }
    }

    cout << "Invalid credentials!\n";
    return false;
}

string User::getUsername() {
    return username;
}

string User::getPassword() {
    string password;
    char ch;

    while (true) {
        ch = _getch();

        if (ch == 13) { // Enter key
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // erase last '*'
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }

    cout << endl;
    return password;
}
