#include "credentials/Credential.hpp"

Credential::Credential(std::string data[3]) : name(data[0]), login(data[1]), password(data[2]) {}

Credential::Credential(std::string inputName, std::string inputLogin, std::string inputPassword) :
        name(std::move(inputName)), login(std::move(inputLogin)), password(std::move(inputPassword)) {}

void Credential::print() const {
    std::cout<< name << "   " << login << "   " << password << std::endl;
}