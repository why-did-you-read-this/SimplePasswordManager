#pragma once

#include "Credential.hpp"
#include <vector>

class Credentials {
private:
    std::vector<Credential> credentials;
    std::string path;
    std::string password;
    bool modified;

    void convertStringToCredentials(const std::string& data);

    std::string convertCredentialsToString();

public:
    const Credential& operator[](std::size_t index) const;

    void deleteFile();

    void createFile(std::string filePath, std::string pswd);

    void readFromFile(std::string filePath, std::string pswd);

    void saveToFile();

    void addCredential(const std::string& inputName, const std::string& inputLogin, const std::string& inputPassword);

    void deleteCredential(size_t index);

    void editCredential(size_t index, const std::string &inputName = "", const std::string &inputLogin="",
                                     const std::string &inputPassword="");

    int findCredentialByName(const std::string& requestName);

    void printAll() const;

    void clear();
};

