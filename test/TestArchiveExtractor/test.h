#pragma once
#include <string>

namespace fs = std::filesystem;

namespace TestConstants
{
fs::path TEST_DIR = fs::current_path();

fs::path TEST_DATA_DIR = TEST_DIR / fs::path("data");
fs::path SAMPLE_EPUB = TEST_DATA_DIR / fs::path("sample.epub");
fs::path DST = TEST_DATA_DIR / fs::path("extracted");
fs::path SAMPLE_ENTRY = DST / fs::path("mimetype");

std::string CHECKSUM_FOLDER_EXPECTED = "37275fc389276ccd59b02ab5b932ec0e5b85477c3e7f41d6a9a58384bab404c3";
std::string CHECKSUM_FILE_EXPECTED = "e468e350d1143eb648f60c7b0bd6031101ec0544a361ca74ecef256ac901f48b";
} // namespace TestConstants
