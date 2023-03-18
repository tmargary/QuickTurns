#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Checksum {
public:
    static std::string generateChecksumForFolder(const fs::path &folder);
    static std::string generateChecksumForFile(const fs::path &file);

private:
    static constexpr size_t SHA256_DIGEST_LENGTH = 32;

    static std::string sha256(const std::string &data);
    static std::string normalizeLineEndings(const std::string &data);
    static std::string readFile(const fs::path &path);
};
