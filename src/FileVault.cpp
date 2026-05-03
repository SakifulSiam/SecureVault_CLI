#include <iostream>
#include <fstream>
#include "FileVault.h"
#include "XOREncryption.h"

using namespace std;

FileVault::FileVault(string username, string password)
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

void FileVault::addPassword(string site, string password)
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
