#include "PasswordChecker.h"
#include <string>
#include <cctype>

string PasswordChecker::checkStrength(string password) {
    int upper = 0, lower = 0, digit = 0, symbol = 0;
    size_t len = password.length();

    for (char c : password) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (isupper(uc)) upper++;
        else if (islower(uc)) lower++;
        else if (isdigit(uc)) digit++;
        else if (ispunct(uc) || isspace(uc)) symbol++;
    }

    // 1. Minimum Length Requirement
    if (len < 6) return "Weak";

    // 2. Strong Criteria: Complexity AND Length
    if (len >= 10 && upper && lower && digit && symbol) {
        return "Strong";
    }

    // 3. Medium Criteria: Requires at least two different types of characters
    int types = (upper > 0) + (lower > 0) + (digit > 0) + (symbol > 0);
    if (len >= 8 && types >= 2) {
        return "Medium";
    }

    return "Weak"; 
}