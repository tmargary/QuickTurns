#include <gtest/gtest.h>

TEST(QuickTurnsTests, DummyTest)
{
    auto dummyVal1 = 0;
    auto dummyVal2 = 0;
    EXPECT_EQ(dummyVal1, dummyVal2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
