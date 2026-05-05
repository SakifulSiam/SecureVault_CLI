#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <functional>
#include <filesystem>
#include "FileVault.h"
#include "XOREncryption.h"

using namespace std;
namespace fs = std::filesystem;

static fs::path dataDir() {
    fs::path dir = fs::current_path() / "data";
    fs::create_directories(dir);
    return dir;
}

FileVault::FileVault(string username, string password)
{
    crypto = make_shared<XORCipher>(password);
    filename = (dataDir() / (username + "_vault.txt")).string();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[Info] No vault found for '" << username << "'. A new vault will be created at:\n";
        cout << "       " << filename << "\n";
        return;
    }

    // Each line: site  hashedSiteUsername  encryptedPassword
    string site, hashedSiteUsername, inpassword;
    while (file >> site >> hashedSiteUsername >> inpassword)
    {
        entries.push_back({site, hashedSiteUsername, inpassword});
    }
}

void FileVault::addPassword(string site, string siteUsername, string password)
{
    if (doesSiteExist(site))
    {
        cout << "Error: The site '" << site << "' already exists!\n";
        return;
    }

    // Hash the site username — stored in vault file, real username kept in memory
    size_t usernameHash = std::hash<string>{}(siteUsername);
    string hashedSiteUsername = to_string(usernameHash);

    string encrypted = crypto->encrypt(password);
    entries.push_back({site, siteUsername, encrypted}); // real username in memory

    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open vault file for writing!\n";
        cout << "Path tried: " << filename << "\n";
        return;
    }
    file << site << " " << hashedSiteUsername << " " << encrypted << "\n";
    file.flush();
    if (file.fail()) {
        cout << "Error: Write to vault failed!\n";
        return;
    }

    cout << "Password saved successfully.\n";
    cout << "[Info] Vault file: " << filename << "\n";
}
