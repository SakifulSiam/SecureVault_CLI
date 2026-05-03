#pragma once
#include <vector>
#include "PasswordEntry.h"
#include "EncryptionEngine.h"
#include "Vault.h"

class FileVault : public Vault {
private:
    string filename;
public:
    FileVault(string username, string password);
    void addPassword(string site, string password) override;
};