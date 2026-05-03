#pragma once
#include <iostream>
#include <string>
using namespace std;

class PasswordGenerator {
    static int default_len;
public:
    string generate(int length) const;
    string generate() const { return generate(default_len); }
    friend ostream &operator<<(ostream &os, const PasswordGenerator &pg)
    {
        cout << "Generated Password: " << pg.generate();
        return os;
    }
    friend istream &operator>>(istream &is, PasswordGenerator &pg)
    {
        cout << "Enter desired password length: ";
        is >> pg.default_len;
        return is;
    }
};

