#pragma once
#include <vector>
#include <memory>
#include "PasswordEntry.h"
#include "EncryptionEngine.h"

class Vault {
protected:
    vector<PasswordEntry> entries;
    shared_ptr<EncryptionEngine> crypto;
public:
    virtual bool doesSiteExist(string name);
    virtual void addPassword(string site, string siteUsername, string password) = 0;
    virtual void viewPasswords();
};