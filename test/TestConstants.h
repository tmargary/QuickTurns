#pragma once

#include <string>

namespace fs = std::filesystem;

namespace TestConstants {
    fs::path TEST_DIR = fs::current_path();
    
    fs::path TEST_DATA_DIR = TEST_DIR / fs::path("data");
    fs::path SAMPLE_EPUB = TEST_DATA_DIR / fs::path("sample.epub");
    fs::path DST = TEST_DATA_DIR / fs::path("extracted");
    fs::path SAMPLE_ENTRY = DST / fs::path("OEBPS") / fs::path("ch01.html");
    
    std::string CHECKSUM_FOLDER_EXPECTED = "e0f8e0434591bfcbaf0d70c84209034bacf2c75888bcd8e5a1bae3fbffc03f67";
    std::string CHECKSUM_FILE_EXPECTED = "77e380b8a5373ffc6e815a7a82e253323faa5bbfb9fa613839dcff7374c7247c";
}

