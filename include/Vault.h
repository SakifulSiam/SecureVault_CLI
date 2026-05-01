#pragma once
#include <vector>
#include "PasswordEntry.h"

class Vault {
private:
    vector<PasswordEntry> entries;
    string filename;
    

public:
    Vault(string username);
    bool doesSiteExist(string name);
    void addPassword(string site, string password);
    void viewPasswords();
};