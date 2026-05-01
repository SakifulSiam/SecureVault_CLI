#pragma once
#include <string>

using namespace std;

class User {
private:
    string username;
    string password;

public:
    bool registerUser();
    bool login();
    string getUsername();
    string getPassword();
};