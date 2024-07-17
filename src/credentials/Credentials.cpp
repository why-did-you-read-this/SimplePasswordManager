#include "credentials/Credentials.hpp"
#include "credentials/Encryption.hpp"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <utility>
#include <sstream>

void Credentials::convertStringToCredentials(const std::string &data) {
    std::istringstream iss(data);
    std::string line;
    while (std::getline(iss, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string passwordData[3];
        for (auto &i: passwordData) {
            std::getline(ss, token, ';');
            i = token;
        }
        credentials.emplace_back(passwordData);
    }
}

std::string Credentials::convertCredentialsToString() {
    std::stringstream ss;

    for (const auto &cred: credentials) {
        ss << cred.name << ";" << cred.login << ";" << cred.password << std::endl;
    }
    std::string data = ss.str();
    return data;
}

void Credentials::createFile(std::string filePath, std::string pswd) {
    if (std::filesystem::exists(filePath)) {
        throw std::logic_error("File already exists");
    }
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Failed to create file at " + filePath);
    }
    file.close();
    path = std::move(filePath);
    password = std::move(pswd);
    modified = false;
}

void Credentials::readFromFile(std::string filePath, std::string pswd) {
    if (!std::filesystem::exists(filePath)) {
        throw std::invalid_argument("File does not exist. Cannot readFromFile file.");
    }
    std::string dataFromFile = Encryption::decryptFileToString(filePath, pswd);
    convertStringToCredentials(dataFromFile);

    path = std::move(filePath);
    password = std::move(pswd);
    modified = false;
}

void Credentials::saveToFile() {
    if (path.empty() or !modified) {
        return;
    }
    if (credentials.empty()) {
        std::ofstream file(path, std::ios::trunc);
        file.close();
        return;
    }
    std::string passwordsData = convertCredentialsToString();
    Encryption::encryptStringToFile(passwordsData, path, password);
}

void Credentials::clear() {
    path.clear();
    password.clear();
    credentials.clear();
    modified = false;
}

void Credentials::deleteFile() {
    if (path.empty()) {
        throw std::invalid_argument("File does not exist. Cannot delete file.");
    }
    if (std::remove(path.c_str()) != 0) {
        throw std::runtime_error("Failed to delete file: " + path);
    }
    clear();
}

void Credentials::addCredential(const std::string &inputName, const std::string &inputLogin,
                                const std::string &inputPassword) {
    if (findCredentialByName(inputName) != -1) {
        throw std::runtime_error("Credential with name '" + inputName + "' already exists.");
    }
    credentials.emplace_back(inputName, inputLogin, inputPassword);
    modified = true;
}

void Credentials::editCredential(size_t index, const std::string &inputName, const std::string &inputLogin,
                                 const std::string &inputPassword) {
    Credential &cred = credentials[index];
    if (!inputName.empty()) {
        cred.name = inputName;
        modified = true;
    }
    if (!inputLogin.empty()) {
        cred.login = inputLogin;
        modified = true;
    }
    if (!inputPassword.empty()) {
        cred.password = inputPassword;
        modified = true;
    }
}

void Credentials::deleteCredential(size_t index) {
    credentials.erase(credentials.begin() + static_cast<long long int>(index));
    modified = true;
}

int Credentials::findCredentialByName(const std::string &requestName) {
    for (size_t i = 0; i < credentials.size(); ++i) {
        auto &cred = credentials[i];
        if (cred.name == requestName) {
            return static_cast<int> (i);
        }
    }
    return -1;
}

void Credentials::printAll() const {
    for (size_t i = 0; i < credentials.size(); ++i) {
        std::cout << i << "   ";
        credentials[i].print();
    }
}

const Credential &Credentials::operator[](std::size_t index) const {
    return credentials.at(index);
}
