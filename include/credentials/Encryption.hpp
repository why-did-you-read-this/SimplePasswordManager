#pragma once

#include <iostream>


class Encryption {
private:
    static bool deriveKeyAndIv(const std::string &password, unsigned char *key, unsigned char *iv, int keyLen);

public:
    static bool
    encryptStringToFile(const std::string &inputString, const std::string &outputFilePath, const std::string &password);

    static std::string decryptFileToString(const std::string &inputFilePath, const std::string &password);
};


