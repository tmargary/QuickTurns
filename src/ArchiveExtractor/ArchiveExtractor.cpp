#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#include "ArchiveExtractor/ArchiveExtractor.h"

using namespace libzippp;
namespace fs = std::filesystem;

std::vector<ZipEntry> EpubExtractor::readEntries(const std::string &source)
{
    zipf.open(ZipArchive::ReadOnly);
    std::vector<ZipEntry> entries = zipf.getEntries();
    return entries;
}

void EpubExtractor::writeEntry(const std::string &output_dir, const std::string &textData)
{
    fs::path outputPath(output_dir);
    fs::create_directories(outputPath.parent_path());
    std::ofstream outputFile(output_dir);
    outputFile << textData;
}

void EpubExtractor::extract()
{
    std::vector<ZipEntry> entries = readEntries(source);
    for (const auto &entry : entries)
    {
        // ZipEntry entry = *ittr;
        fs::path name = entry.getName();
        std::string textData = entry.readAsText();
        std::string output_file = output_dir / name;
        writeEntry(output_file, textData);
    }
}

std::unique_ptr<ArchiveExtractor> createExtractor(const std::string &source, const std::string &destinationDir)
{
    std::string extension = fs::path(source).extension().string();
    if (extension == ".epub")
    {
        return std::make_unique<EpubExtractor>(source, destinationDir);
    }
    throw std::runtime_error("Unsupported file format.");
}