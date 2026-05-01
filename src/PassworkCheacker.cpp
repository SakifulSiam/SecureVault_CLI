#include "PasswordChecker.h"
#include <cctype>

string PasswordChecker::checkStrength(string password) {
    int upper = 0, lower = 0, digit = 0, symbol = 0;

    for (char c : password) {
        if (isupper(c)) upper++;
        else if (islower(c)) lower++;
        else if (isdigit(c)) digit++;
        else symbol++;
    }

    if (password.length() < 6)
        return "Weak";

    if (upper && lower && digit && symbol && password.length() >= 10)
        return "Strong";

    return "Medium";
}