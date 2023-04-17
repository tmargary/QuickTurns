#pragma once

#include "libzippp.h"
#include <filesystem>
#include <memory>
#include <string>
#include <iostream>

using namespace libzippp;
namespace fs = std::filesystem;

class ArchiveExtractor
{
  public:
    virtual std::vector<ZipEntry> readEntries(const fs::path &source) = 0;
    virtual void writeEntry(const fs::path &output_dir, const std::string &textData) = 0;
    virtual void extract() = 0;
    virtual ~ArchiveExtractor() = default;
};

class EpubExtractor : public ArchiveExtractor
{
  public:
    EpubExtractor(const std::string &src, const std::string &out) : source(src), output_dir(out), zipf(src)
    {
    }

    EpubExtractor(const fs::path &src, const fs::path &out) : EpubExtractor(src.string(), out.string())
    {
    }

    ~EpubExtractor() = default;

    std::vector<ZipEntry> readEntries(const fs::path &source) override;
    void writeEntry(const fs::path &output_dir, const std::string &textData) override;
    void extract() override;

  private:
    fs::path source;
    fs::path output_dir;
    ZipArchive zipf;
};

std::unique_ptr<ArchiveExtractor> createExtractor(const fs::path &source, const fs::path &destinationDir);