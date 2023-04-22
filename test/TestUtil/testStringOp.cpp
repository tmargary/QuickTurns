#include "StringOp.h"
#include "gtest/gtest.h"


TEST(UtilTest, Basic) {
    std::string input = "My Example Text";
    std::string expected_output = "my_example_text";
    std::string output = createUnderscoreName(input);
    EXPECT_EQ(expected_output, output);
}

TEST(UtilTest, ConsecutiveSpecialChars) {
    std::string input = "My #^@Example@!Text";
    std::string expected_output = "my_example_text";
    std::string output = createUnderscoreName(input);
    EXPECT_EQ(expected_output, output);
}

TEST(UtilTest, TrailingUnderscores) {
    std::string input = "My Example Text%%%";
    std::string expected_output = "my_example_text";
    std::string output = createUnderscoreName(input);
    EXPECT_EQ(expected_output, output);
}

TEST(UtilTest, EmptyString) {
    std::string input = "";
    std::string expected_output = "";
    std::string output = createUnderscoreName(input);
    EXPECT_EQ(expected_output, output);
}

TEST(UtilTest, AlphanumericOnly) {
    std::string input = "MyExampleText123";
    std::string expected_output = "myexampletext123";
    std::string output = createUnderscoreName(input);
    EXPECT_EQ(expected_output, output);
}
