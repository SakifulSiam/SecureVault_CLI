#include <iostream>
#include <fstream>
#include "Vault.h"
#include "XOREncryption.h"

using namespace std;

Vault::Vault(string username, string password)
{
    crypto = make_shared<XORCipher>(password);
    filename = "data/" + username + "_vault.txt";

    ifstream file(filename);
    string site, inpassword;

    while (file >> site >> inpassword)
    {
        entries.push_back({site, inpassword});
    }
}

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

void Vault::addPassword(string site, string password)
{

    if (doesSiteExist(site))
    {
        cout << "Error: The site '" << site << "' already exists!\n";
    }
    else
    {
        string encrypted = crypto->encrypt(password);
        entries.push_back({site, encrypted});
        cout << "Registration successful.\n";
        ofstream file(filename, ios::app);
        file << site << " " << encrypted << endl;
    }
}

void Vault::viewPasswords()
{
    for (auto &e : entries)
    {
        cout << e.site << " : "
             << crypto->decrypt(e.password) << endl;
    }
}