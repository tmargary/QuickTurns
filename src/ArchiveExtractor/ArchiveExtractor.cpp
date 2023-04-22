#include "ArchiveExtractor.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

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

std::string EpubExtractor::readSpecificEntry(const std::string &entryName)
{
    const std::vector<ZipEntry> entries = readEntries(source);

    for (const auto &entry : entries)
    {
        const std::string currentEntryName = entry.getName();
        if (entryName.size() <= currentEntryName.size() && 
            currentEntryName.rfind(entryName) == (currentEntryName.size() - entryName.size()))
        {
            return entry.readAsText();
        }
    }

    std::cerr << "Warning: Entry not found: " << entryName << std::endl;
    return "";
}

bool EpubExtractor::extractSpecificEntry(const std::string &entryName, const fs::path &output_file)
{
    const std::string textData = readSpecificEntry(entryName);
    if (!textData.empty())
    {
        writeEntry(output_file, textData);
        return true;
    }
    return false;
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