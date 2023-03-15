#include "ArchiveExtractor/ArchiveExtractor.h"
#include "Util/Util.h"
#include <gtest/gtest.h>

std::string get_test_data_dir(){
    const boost::filesystem::path source_file(__FILE__);
    const std::string test_dir = source_file.parent_path().string();
    return test_dir + "/../build/test/data";
}

TEST(ArchiveExtractorTest, TestEpubExtractor) {

    const std::string test_data_dir = get_test_data_dir();
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