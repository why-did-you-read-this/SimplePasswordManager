#include "credentials/Encryption.hpp"
#include <openssl/evp.h>
#include <fstream>
#include <vector>
#include <string>

bool Encryption::deriveKeyAndIv(const std::string &password, unsigned char *key, unsigned char *iv, int keyLen) {
    const EVP_MD *dgst = EVP_sha256();
    if (!dgst) {
        throw std::runtime_error("Error obtaining hash function.");
    }

    if (EVP_BytesToKey(EVP_aes_256_cbc(), dgst, nullptr,
                       reinterpret_cast<const unsigned char *>(password.c_str()), static_cast<int>(password.length()),
                       1, key, iv) != keyLen) {
        throw std::runtime_error("Error generating key and IV.");
    }

    return true;
}

bool Encryption::encryptStringToFile(const std::string &inputString, const std::string &outputFilePath,
                                     const std::string &password) {
    unsigned char key[32], iv[16];
    deriveKeyAndIv(password, key, iv, sizeof(key));

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Error opening output file.");
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Error creating encryption context.");
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error initializing encryption.");
    }

    std::vector<unsigned char> buffer(inputString.begin(), inputString.end());
    std::vector<unsigned char> cipherBuffer(buffer.size() + static_cast<std::size_t>(EVP_CIPHER_CTX_block_size(ctx)));
    int cipherBytesWritten = 0;

    if (EVP_EncryptUpdate(ctx, cipherBuffer.data(), &cipherBytesWritten, buffer.data(),
                          static_cast<int>(buffer.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error encrypting data.");
    }

    int finalBytesWritten = 0;
    if (EVP_EncryptFinal_ex(ctx, cipherBuffer.data() + cipherBytesWritten, &finalBytesWritten) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error finalizing encryption.");
    }

    cipherBytesWritten += finalBytesWritten;
    outputFile.write(reinterpret_cast<char *>(cipherBuffer.data()), cipherBytesWritten);

    EVP_CIPHER_CTX_free(ctx);
    outputFile.close();
    return true;
}

std::string Encryption::decryptFileToString(const std::string &inputFilePath, const std::string &password) {
    unsigned char key[32], iv[16];
    deriveKeyAndIv(password, key, iv, sizeof(key));

    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Error opening input file.");
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Error creating decryption context.");
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error initializing decryption.");
    }

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    std::vector<unsigned char> plainBuffer(buffer.size() + static_cast<std::size_t>(EVP_CIPHER_CTX_block_size(ctx)));
    int plainBytesWritten = 0;

    if (EVP_DecryptUpdate(ctx, plainBuffer.data(), &plainBytesWritten, buffer.data(),
                          static_cast<int>(buffer.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error decrypting data.");
    }

    int finalBytesWritten = 0;
    if (EVP_DecryptFinal_ex(ctx, plainBuffer.data() + plainBytesWritten, &finalBytesWritten) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Error finalizing decryption.");
    }

    plainBytesWritten += finalBytesWritten;
    EVP_CIPHER_CTX_free(ctx);
    inputFile.close();

    return std::string(plainBuffer.begin(), plainBuffer.begin() + plainBytesWritten);
}