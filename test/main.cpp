#include "ArchiveExtractor/ArchiveExtractor.h"
#include "Util/Util.h"
#include <gtest/gtest.h>

TEST(ArchiveExtractorTest, TestEpubExtractor) {
    const std::string test_data_dir = boost::filesystem::current_path().string() + "/data";
    const std::string src = test_data_dir + "/sample.epub";
    const std::string dst = test_data_dir + "/extracted/";
    const std::string entryFile = test_data_dir + "/extracted/mimetype";
    
    // get the extractor object from the factory function and perform the extraction
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(src, dst);

    extractor->extract(src, dst);

    ASSERT_TRUE(boost::filesystem::exists(entryFile));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}