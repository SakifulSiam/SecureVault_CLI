#pragma once
#include "EncryptionEngine.h"

class XORCipher : public EncryptionEngine {
private:
    string key;

    string xorProcess(const string& data) {
        string result = data;

        for (size_t i = 0; i < data.size(); i++) {
            result[i] = data[i] ^ key[i % key.size()];
        }

        return result;
    }

public:
    XORCipher(string k) : key(k) {}

    string encrypt(string data) override {
        return xorProcess(data);
    }

    string decrypt(string data) override {
        return xorProcess(data);
    }
};