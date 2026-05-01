#pragma once
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;
    uint64_t passwordHash;
public:
    bool registerUser();
    bool login();
    string getUsername();
    string getPassword() {
        return password;
    }
    string inputPassword();
    unsigned long long hash(string password)
    {
        unsigned long long hash = 5381;
        unsigned long long salt = 131;

        for (int i = 0; i < password.length(); i++)
        {
            char c = password[i];
            hash = hash * salt + (c + i * 7);
        }

        return hash;
    }
};