#include "password_generator/password_generator.hpp"
#include <string>
#include <random>

std::string generatePassword(size_t length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> distrib(0, charset.length() - 1);

    std::string password;
    password.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        password += charset[distrib(gen)];
    }

    return password;
}