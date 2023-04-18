#include "ArchiveExtractor.h"

#include "test.h"
#include "Checksum.h"
#include <gtest/gtest.h>

using namespace TestConstants;
using namespace std;

TEST(ArchiveExtractorTest, TestEpubExtractorFolderCheckSum)
{

    // extract
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(SAMPLE_EPUB, DST);
    extractor->extract();

    // checksum
    const std::string checksum_result = Checksum::generateChecksumForFolder(DST);

    ASSERT_EQ(checksum_result, CHECKSUM_FOLDER_EXPECTED);
}

TEST(ArchiveExtractorTest, TestEpubExtractorFileCheckSum)
{

    // extract
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(SAMPLE_EPUB, DST);
    extractor->extract();

    // checksum
    const std::string checksum_result = Checksum::generateChecksumForFile(SAMPLE_ENTRY);

    ASSERT_EQ(checksum_result, CHECKSUM_FILE_EXPECTED);
}
