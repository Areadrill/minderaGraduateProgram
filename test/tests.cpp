#include <gtest/gtest.h>

TEST(lol, xd){
    int l = 1;
    EXPECT_EQ(l, 1);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}