#pragma once

#include <iostream>

struct Credential {
    std::string name;
    std::string login;
    std::string password;

    explicit Credential(std::string data[3]);

    Credential(std::string inputName, std::string inputLogin, std::string inputPassword);

    void print() const;
};

