#include "main_interactions.hpp"
#include "password_generator/password_generator.hpp"
#include "credentials/Credentials.hpp"
#include <iostream>
#include <limits>

void showAboutProgram() {
    std::cout << "Simple Password Manager" << std::endl;
    std::cout << "This program allows you to generate strong passwords and securely store them using encryption"
              << std::endl;
    std::cout << "Version: 1.0" << std::endl;
    std::cout << "Author: Zakhar Bogdanchikov" << std::endl;
}

void getGeneratedPassword() {
    size_t passwordLength;
    std::cout << "Enter password length:" << std::endl;
    std::cin >> passwordLength;
    std::cout << "Password:" << std::endl;
    std::cout << generatePassword(passwordLength) << std::endl;
}

void createSPMFile(Credentials &credentials) {
    std::string fileName;
    std::string password;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> fileName;
    fileName += ".spm";
    std::cout << "Enter the password:" << std::endl;
    std::cin >> password;
    credentials.createFile(fileName, password);
}

void openSPMFile(Credentials &credentials) {
    std::string fileName;
    std::string password;
    std::cout << "Enter path to .spm file:" << std::endl;
    std::cin >> fileName;
    std::cout << "Enter the password:" << std::endl;
    std::cin >> password;

    credentials.readFromFile(fileName, password);
}

void findPasswordByName(Credentials &credentials) {
    std::string name;
    std::cout << "Enter name:" << std::endl;
    std::cin >> name;
    int index = credentials.findCredentialByName(name);
    if (index == -1) {
        std::cout << "Credential with name '" + name + "' do not exist" << std::endl;
    } else {
        std::cout << index << " ";
        credentials[static_cast<size_t>(index)].print();
    }
}

void addPassword(Credentials &credentials) {
    std::string name;
    std::string login;
    std::string password;
    std::cout << "Enter name:" << std::endl;
    std::cin >> name;
    std::cout << "Enter login:" << std::endl;
    std::cin >> login;
    std::cout << "Enter password:" << std::endl;
    std::cin >> password;
    credentials.addCredential(name, login, password);
}

void editPassword(Credentials &credentials) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    size_t index;
    std::string name;
    std::string login;
    std::string password;
    std::string s;
    std::cout << "Enter index:" << std::endl;
    std::getline(std::cin, s);
    index = std::stoul(s);
    std::cout << "Credential with index " << index << ":" << std::endl;
    credentials[index].print();
    std::cout << "If you don't want to change any credentials, press enter" << std::endl;
    std::cout << "Enter new name:" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Enter new login:" << std::endl;
    std::getline(std::cin, login);
    std::cout << "Enter new password:" << std::endl;
    std::getline(std::cin, password);
    credentials.editCredential(index, name, login, password);
    std::cout << "Credential with index " << index << ":" << std::endl;
    credentials[index].print();
}

void deletePassword(Credentials &credentials){
    size_t index;
    std::cout << "Enter index:" << std::endl;
    std::cin >> index;
    credentials.deleteCredential(index);
}
