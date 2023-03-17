#pragma once

#include <string>

namespace TestConstants {
    const std::string TEST_DIR(boost::filesystem::path(__FILE__).parent_path().string());
    const std::string TEST_DATA_DIR = TEST_DIR + "/data";
    const std::string SAMPLE_EPUB = TEST_DATA_DIR + "/sample.epub";
    const std::string DST = TEST_DATA_DIR + "/extracted/";
    const std::string SAMPLE_ENTRY = TEST_DATA_DIR + "/extracted/OEBPS/ch01.html";
    
    const std::string CHECKSUM_FOLDER_EXPECTED = "297a23c9b57686e3dca5c0244d1c994521ede2cea2945145faea15d85a47f662";
    const std::string CHECKSUM_FILE_EXPECTED = "77e380b8a5373ffc6e815a7a82e253323faa5bbfb9fa613839dcff7374c7247c";
}