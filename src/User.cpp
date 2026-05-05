#include <iostream>
#include <fstream>
#include <filesystem>
#include "conio_cross.h"
#include "User.h"

using namespace std;
namespace fs = std::filesystem;

// Returns absolute path to data/ dir beside the binary (creates it if missing)
static fs::path dataDir() {
    fs::path dir = fs::current_path() / "data";
    fs::create_directories(dir);
    return dir;
}

static fs::path usersFile() {
    return dataDir() / "users.txt";
}

bool User::registerUser() {
    cout << "Enter username: ";
    cin >> username;

    // Duplicate check
    {
        ifstream checkFile(usersFile());
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

    ofstream file(usersFile(), ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open users file for writing!\n";
        cout << "Path tried: " << usersFile() << "\n";
        return false;
    }
    file << username << " " << passwordHash << "\n";
    file.flush();
    if (file.fail()) {
        cout << "Error: Write to disk failed!\n";
        return false;
    }

    cout << "User registered successfully!\n";
    cout << "[Info] Data saved to: " << usersFile() << "\n";
    return true;
}

bool User::login() {
    string inputUser, inputPass;

    cout << "Username: ";
    cin >> inputUser;

    cout << "Password: " << flush;
    inputPass = inputPassword();
    passwordHash = hash(inputPass);

    ifstream file(usersFile());
    if (!file.is_open()) {
        cout << "Error: No registered users found. Please register first.\n";
        return false;
    }

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

string User::getDataDir() {
    return dataDir().string();
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
