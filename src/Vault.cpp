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
    for (auto &e : entries)
    {
        cout << e.site << " : "
             << crypto->decrypt(e.password) << endl;
    }
}