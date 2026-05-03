#include "PasswordGenerator.h"
#include <random>

int PasswordGenerator::default_len = 8;

string PasswordGenerator::generate(int length) const {
    string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, chars.size() - 1);

    string password = "";

    for (int i = 0; i < length; i++) {
        password += chars[dist(gen)];
    }

    return password;
}