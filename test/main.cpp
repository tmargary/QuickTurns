#include "ArchiveExtractor/ArchiveExtractor.h"
#include "Util/Util.h"
#include <gtest/gtest.h>

using namespace std;

TEST(ArchiveExtractorTest, TestEpubExtractorFolderCheckSum) {
    const std::string checksum_expected = "fc1f88dd71e45b1cdfc928a60764f1f59fc5eaa9da78a01b27d7c860ff9f023b";
    const std::string test_dir(boost::filesystem::path(__FILE__).parent_path().string());
    const std::string test_data_dir = test_dir + "/data";
    const std::string src = test_data_dir + "/sample.epub";
    const std::string dst = test_data_dir + "/extracted/";
    
    // extract
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(src, dst);
    extractor->extract(src, dst);

    cout << "test_data_dir: "<< test_data_dir << endl << endl;

    // extract
    std::string checksum_result = generateChecksumForFolder(dst);

    ASSERT_EQ(checksum_result, checksum_expected);
}

TEST(ArchiveExtractorTest, TestEpubExtractorFileCheckSum) {
    const std::string checksum_expected = "77e380b8a5373ffc6e815a7a82e253323faa5bbfb9fa613839dcff7374c7247c";
    
    const std::string test_dir(boost::filesystem::path(__FILE__).parent_path().string());
    const std::string test_data_dir = test_dir + "/data";
    const std::string src = test_data_dir + "/sample.epub";
    const std::string dst = test_data_dir + "/extracted/";
    const std::string entry_file = test_data_dir + "/extracted/OEBPS/ch01.html";
    
    // get the extractor object from the factory function and perform the extraction
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(src, dst);
    extractor->extract(src, dst);

    std::string checksum_result = generateChecksumForFile(entry_file);

    ASSERT_EQ(checksum_result, checksum_expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
