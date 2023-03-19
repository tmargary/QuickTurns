#include <gtest/gtest.h>
#include "ArchiveExtractor/ArchiveExtractor.h"
#include "Util/Checksum.h"
#include "TestConstants.h"

using namespace TestConstants;
using namespace std;

TEST(ArchiveExtractorTest, TestEpubExtractorFolderCheckSum) {

    
    // extract
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(SAMPLE_EPUB, DST);
    extractor->extract();

    // checksum
    const std::string checksum_result = Checksum::generateChecksumForFolder(DST);

    ASSERT_EQ(checksum_result, CHECKSUM_FOLDER_EXPECTED);
}

TEST(ArchiveExtractorTest, TestEpubExtractorFileCheckSum) {
    
    // extract
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(SAMPLE_EPUB, DST);
    extractor->extract();

    // checksum
    const std::string checksum_result = Checksum::generateChecksumForFile(SAMPLE_ENTRY);

    ASSERT_EQ(checksum_result, CHECKSUM_FILE_EXPECTED);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
