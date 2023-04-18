#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "ArchiveExtractor.h"

using namespace libzippp;
namespace fs = std::filesystem;

std::vector<ZipEntry> EpubExtractor::readEntries(const fs::path &source)
{
    zipf.open(ZipArchive::ReadOnly);
    std::vector<ZipEntry> entries = zipf.getEntries();
    return entries;
}

void EpubExtractor::writeEntry(const fs::path &output_dir, const std::string &textData)
{
    fs::create_directories(output_dir.parent_path());
    std::ofstream outputFile(output_dir);
    outputFile << textData;
}

void EpubExtractor::extract()
{
    const std::vector<ZipEntry> entries = readEntries(source);
    for (const auto &entry : entries)
    {
        const fs::path name = entry.getName();
        const std::string textData = entry.readAsText();
        const fs::path output_file = output_dir / name;
        writeEntry(output_file, textData);
    }
}

std::unique_ptr<ArchiveExtractor> createExtractor(const fs::path &source, const fs::path &destinationDir)
{
    const std::string extension = fs::path(source).extension().string();
    if (extension == ".epub")
    {
        return std::make_unique<EpubExtractor>(source, destinationDir);
    }
    throw std::runtime_error("Unsupported file format.");
}

std::string EpubExtractor::readSpecificEntry(const std::string& entryName)
{
    const std::vector<ZipEntry> entries = readEntries(source);
    auto it = std::find_if(entries.begin(), entries.end(), [&entryName](const ZipEntry& entry) {
        std::string currentEntryName = entry.getName();
        return currentEntryName.rfind(entryName) == (currentEntryName.size() - entryName.size());
    });

    if (it != entries.end())
    {
        return it->readAsText();
    }

    throw std::runtime_error("Entry not found.");
}
