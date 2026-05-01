#include "XOREncryption.h"
// #include <sstream>
// #include <iomanip>

string XOREncryption::encrypt(string data) {
    for (char &c : data) {
        c = c ^ key;
    }
    return data;
}

string XOREncryption::decrypt(string data) {
    return encrypt(data); // XOR is reversible
}

// string hashPassword(const string& password) {
//     if (password.empty()) return "";
 
//     const unsigned char SALT = 0xA5; // fixed salt constant
//     string hashed = password;
//     int n = password.size();
 
//     // Pass 1: rolling XOR forward (each byte XOR'd with the next)
//     for (int i = 0; i < n - 1; i++) {
//         hashed[i] = password[i] ^ password[i + 1];
//     }
//     hashed[n - 1] = password[n - 1] ^ password[0]; // wrap last with first
 
//     // Pass 2: XOR with index + salt to make position and length matter
//     for (int i = 0; i < n; i++) {
//         hashed[i] = hashed[i] ^ (unsigned char)(i + 1) ^ SALT;
//     }
 
//     // Pass 3: accumulate (each byte XOR'd with all previous bytes combined)
//     unsigned char acc = 0;
//     for (int i = 0; i < n; i++) {
//         acc ^= (unsigned char)hashed[i];
//         hashed[i] = acc;
//     }
 
//     // Convert to hex string for safe storage
//     ostringstream oss;
//     for (int i = 0; i < n; i++) {
//         oss << hex << setw(2) << setfill('0')
//             << (int)(unsigned char)hashed[i];
//     }
//     return oss.str();
// }