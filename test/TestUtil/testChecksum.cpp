#include "Checksum.h"
#include "gtest/gtest.h"
#include <fstream>

class ChecksumTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Code to run before each test, if needed
    }

    void TearDown() override {
        // Code to run after each test, if needed
    }
};

TEST_F(ChecksumTest, Sha256) {
    std::string input = "test";
    std::string expected_output = "9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08";
    std::string output = Checksum::sha256(input);
    EXPECT_EQ(expected_output, output);
}

TEST_F(ChecksumTest, NormalizeLineEndings) {
    std::string input = "line1\r\nline2\r\nline3\r";
    std::string expected_output = "line1\nline2\nline3";
    std::string output = Checksum::normalizeLineEndings(input);
    EXPECT_EQ(expected_output, output);
}

TEST_F(ChecksumTest, GenerateChecksumForFile) {
    // Create a temporary file with known content
    fs::path tmp_file = "test_file.txt";
    std::ofstream tmp_stream(tmp_file);
    tmp_stream << "test\n";
    tmp_stream.close();

    std::string expected_output = "f2ca1bb6c7e907d06dafe4687e579fce76b37e4e93b7605022da52e6ccc26fd2";
    std::string output = Checksum::generateChecksumForFile(tmp_file);
    EXPECT_EQ(expected_output, output);

    // Clean up the temporary file
    fs::remove(tmp_file);
}
