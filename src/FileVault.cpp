#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <functional>
#include "FileVault.h"
#include "XOREncryption.h"

using namespace std;

FileVault::FileVault(string username, string password)
{
    crypto = make_shared<XORCipher>(password);
    filename = "data/" + username + "_vault.txt";

    try {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Vault file not found. A new vault will be created.");
        }
        // Each line: site  hashedSiteUsername  encryptedPassword
        string site, hashedSiteUsername, inpassword;
        while (file >> site >> hashedSiteUsername >> inpassword)
        {
            entries.push_back({site, hashedSiteUsername, inpassword});
        }
    } catch (const runtime_error& e) {
        cout << "[Info] " << e.what() << "\n";
    }
}

void FileVault::addPassword(string site, string siteUsername, string password)
{
    if (doesSiteExist(site))
    {
        cout << "Error: The site '" << site << "' already exists!\n";
    }
    else
    {
        // Hash the site username before storing
        size_t usernameHash = std::hash<string>{}(siteUsername);
        string hashedSiteUsername = to_string(usernameHash);

        string encrypted = crypto->encrypt(password);
        entries.push_back({site, hashedSiteUsername, encrypted});
        cout << "Password saved successfully.\n";

        ofstream file(filename, ios::app);
        file << site << " " << hashedSiteUsername << " " << encrypted << endl;
    }
}

