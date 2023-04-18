#include "Checksum.h"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>
#include <vector>

std::string Checksum::sha256(const std::string &data)
{
    std::array<unsigned char, SHA256_DIGEST_LENGTH> hash{};
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, data.c_str(), data.length());
    unsigned int digest_len{};
    EVP_DigestFinal_ex(ctx, hash.data(), &digest_len);
    EVP_MD_CTX_free(ctx);

    std::stringstream sstream;
    for (const auto &byte : hash)
    {
        sstream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return sstream.str();
}

std::string Checksum::normalizeLineEndings(const std::string &data)
{
    std::string normalized;
    normalized.reserve(data.size());

    for (const auto &symbol : data)
    {
        if (symbol != '\r')
        {
            normalized.push_back(symbol);
        }
    }

    return normalized;
}

std::string Checksum::readFile(const fs::path &path)
{
    const std::ifstream file(path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    const std::string content = buffer.str();
    return normalizeLineEndings(content);
}

std::string Checksum::generateChecksumForFolder(const fs::path &folder)
{
    std::vector<std::string> fileHashes;

    for (const auto &entry : fs::directory_iterator(folder))
    {
        if (entry.is_regular_file())
        {
            const std::string fileContent = readFile(entry.path());
            const std::string fileHash = sha256(fileContent);
            fileHashes.push_back(fileHash);
        }
    }

    std::sort(fileHashes.begin(), fileHashes.end());

    std::string combinedHashes;
    for (const auto &hash : fileHashes)
    {
        combinedHashes += hash;
    }

    return sha256(combinedHashes);
}

std::string Checksum::generateChecksumForFile(const fs::path &file)
{
    if (!fs::is_regular_file(file))
    {
        throw std::runtime_error("Invalid file path");
    }

    const std::string fileContent = readFile(file);
    return sha256(fileContent);
}

