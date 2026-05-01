#include <iostream>
#include <fstream>
#include "conio_cross.h"
#include "User.h"

using namespace std;


bool User::registerUser() {
    cout << "Enter username: ";
    cin >> username;
    
    cout << "Enter password: " << flush;
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
            username = inputUser;
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

    clear_stdin_buffer(); 

    while (true) {
        ch = getch_cross();

        if (ch == KEY_ENTER) {
            break;
        }
        else if (ch == KEY_BACKSPACE) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b" << flush;
            }
        }
        else if (isprint(static_cast<unsigned char>(ch))) {
            password.push_back(ch);
            cout << '*' << flush;
        }
    }

    cout << endl;
    return password;
}