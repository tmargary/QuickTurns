#include <string>
#include <filesystem>

namespace fs = std::filesystem;

std::string generateChecksumForFile(const fs::path &file);
std::string generateChecksumForFolder(const fs::path &folder);