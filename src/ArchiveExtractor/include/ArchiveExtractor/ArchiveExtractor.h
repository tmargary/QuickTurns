#pragma once

#include "libzippp.h"
#include <memory>
#include <string>
#include <boost/filesystem.hpp>

using namespace libzippp;

class ArchiveExtractor
{
  public:
    virtual std::vector<ZipEntry> readEntries(const std::string &source) = 0;
    virtual void writeEntry(const std::string &outputFilename, const std::string &textData) = 0;
    virtual void extract(const std::string &source, const std::string &destinationDir) = 0;
    virtual ~ArchiveExtractor()
    {
    }
};

class EpubExtractor : public ArchiveExtractor
{
  public:
    EpubExtractor(const std::string &src, const std::string &out) : source(src), outputFilename(out), zipf(src)
    {
    }
    ~EpubExtractor() = default;

    std::vector<ZipEntry> readEntries(const std::string &source) override;
    void writeEntry(const std::string &outputFilename, const std::string &textData) override;
    void extract(const std::string &source, const std::string &destinationDir);

  private:
    const std::string source;
    const std::string outputFilename;
    ZipArchive zipf;
};

std::unique_ptr<ArchiveExtractor> createExtractor(const std::string& source, const std::string &destinationDir);