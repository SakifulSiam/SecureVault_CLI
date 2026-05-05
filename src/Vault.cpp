#include <iostream>
#include <fstream>
#include "Vault.h"
#include "XOREncryption.h"

using namespace std;

bool Vault::doesSiteExist(std::string name)
{
    for (const auto &entry : entries)
    {
        if (entry.site == name)
        {
            return true; // Match found
        }
    }
    return false; // No match
}

void Vault::viewPasswords()
{
    if (entries.empty()) {
        cout << "No passwords stored yet.\n";
        return;
    }
    cout << "\n--- Stored Passwords ---\n";
    for (auto &e : entries)
    {
        cout << "Site     : " << e.site << "\n"
             << "Username : " << e.siteUsername << "\n"
             << "Password : " << crypto->decrypt(e.password) << "\n"
             << "------------------------\n";
    }
}