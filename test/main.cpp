#include "ArchiveExtractor/ArchiveExtractor.h"
#include "Util/Util.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(ArchiveExtractorTest, TestEpubExtractor) {
    // get the project root and other paths
    std::string cwd = get_project_root_dir();
    
    const std::string source = boost::filesystem::absolute(
        "test/data/sample.epub", cwd).string();
    const std::string destinationDir = boost::filesystem::absolute(
        "test/data/extracted/", cwd).string();
    const std::string entryFile = boost::filesystem::absolute(
        "test/data/extracted/mimetype", cwd).string();
    
    // get the extractor object from the factory function and perform the extraction
    std::unique_ptr<ArchiveExtractor> extractor = createExtractor(source, destinationDir);
    extractor->extract(source, destinationDir);

    // get the file content
    const std::string file_content = read_file_contents(entryFile);

    // asserts
    ASSERT_TRUE(boost::filesystem::exists(entryFile));
    ASSERT_TRUE(file_content == "application/epub+zip");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}