#pragma once
#include <string>
#include <sstream>
using namespace std;

// Generic utility: convert any value to string
template <typename T>
string toString(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

class PasswordChecker
{
public:
    string checkStrength(string password);
};
