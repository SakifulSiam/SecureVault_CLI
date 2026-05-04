#pragma once
#include <string>
using namespace std;

struct PasswordEntry {
    string site;
    string siteUsername;   // username for that site/service
    string password;
};