#pragma once
#include "EncryptionEngine.h"

class XOREncryption : public EncryptionEngine {
private:
    char key = 'K';

public:
    string encrypt(string data);
    string decrypt(string data);
};