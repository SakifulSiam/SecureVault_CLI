#pragma once
#include <vector>
#include "PasswordEntry.h"
#include "EncryptionEngine.h"

class Vault {
private:
    vector<PasswordEntry> entries;
    string filename;
    shared_ptr<EncryptionEngine> crypto;
public:
    Vault(string username, string password);
    bool doesSiteExist(string name);
    void addPassword(string site, string password);
    void viewPasswords();
};