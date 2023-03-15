#include <boost/filesystem.hpp>
#include <fstream>
#include <string>
#include <vector>

#include "ArchiveExtractor/ArchiveExtractor.h"

using namespace libzippp;

std::vector<ZipEntry> EpubExtractor::readEntries(const std::string &source)
{
    zipf.open(ZipArchive::ReadOnly);
    std::vector<ZipEntry> entries = zipf.getEntries();
    return entries;
}

void EpubExtractor::writeEntry(const std::string &outputFilename, const std::string &textData)
{
    boost::filesystem::path outputPath(outputFilename);
    boost::filesystem::create_directories(outputPath.parent_path());
    std::ofstream outputFile(outputFilename);
    outputFile << textData;
}

void EpubExtractor::extract(const std::string &source, const std::string &destinationDir)
{
    std::vector<ZipEntry> entries = readEntries(source);
    for (const auto &entry : entries)
    {
        // ZipEntry entry = *ittr;
        std::string name = entry.getName();
        std::string textData = entry.readAsText();
        std::string outputFilename = destinationDir + name;
        writeEntry(outputFilename, textData);
    }
}

std::unique_ptr<ArchiveExtractor> createExtractor(const std::string &source, const std::string &destinationDir)
{
    std::string extension = boost::filesystem::extension(source);
    if (extension == ".epub")
    {
        return std::make_unique<EpubExtractor>(source, destinationDir);
    }
    throw std::runtime_error("Unsupported file format.");
}