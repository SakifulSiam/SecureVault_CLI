#include <iostream>
#include <fstream>
#include "conio_cross.h"
#include "User.h"

using namespace std;


bool User::registerUser() {
    cout << "Enter username: ";
    cin >> username;

    // Check if username already exists
    {
        ifstream checkFile("data/users.txt");
        string fileUser, fileHash;
        while (checkFile >> fileUser >> fileHash) {
            if (fileUser == username) {
                cout << "Error: User '" << username << "' is already registered!\n";
                return false;
            }
        }
    }

    cout << "Enter password: " << flush;
    password = inputPassword();
    passwordHash = hash(password);
    ofstream file("data/users.txt", ios::app);
    file << username << " " << passwordHash << endl;

    cout << "User registered successfully!\n";
    return true;
}

bool User::login() {
    string inputUser, inputPass;
    
    cout << "Username: ";
    cin >> inputUser;
    
    cout << "Password: " << flush;
    inputPass = inputPassword();
    passwordHash = hash(inputPass);
    
    ifstream file("data/users.txt");
    string fileUser, filePass;
    
    while (file >> fileUser >> filePass) {
        if (fileUser == inputUser && filePass == to_string(passwordHash)) {
            username = inputUser;
            password = inputPass;
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

string User::inputPassword() {
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