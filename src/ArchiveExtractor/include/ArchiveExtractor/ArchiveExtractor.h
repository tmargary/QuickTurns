#pragma once

#include "libzippp.h"
#include <boost/filesystem.hpp>
#include <memory>
#include <string>
#include <iostream>

using namespace libzippp;

class ArchiveExtractor
{
  public:
    virtual std::vector<ZipEntry> readEntries(const std::string &source) = 0;
    virtual void writeEntry(const std::string &output_dir, const std::string &textData) = 0;
    virtual void extract() = 0;
    virtual ~ArchiveExtractor() = default;
};

class EpubExtractor : public ArchiveExtractor
{
  public:
    EpubExtractor(const std::string &src, const std::string &out) : source(src), output_dir(out), zipf(src)
    {
        std::cout;
    }
    ~EpubExtractor() = default;

    std::vector<ZipEntry> readEntries(const std::string &source) override;
    void writeEntry(const std::string &output_dir, const std::string &textData) override;
    void extract() override;

  private:
    const std::string source;
    const std::string output_dir;
    ZipArchive zipf;
};

std::unique_ptr<ArchiveExtractor> createExtractor(const std::string &source, const std::string &destinationDir);