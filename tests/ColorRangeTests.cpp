#include <gtest/gtest.h>

#include "Style/ColorRange.h"

using namespace Cesame;

class ColorRangeTests : public testing::Test {
protected:
    ColorRange low = ColorRange(0, 50, QColor(255, 255, 255));
    ColorRange mid = ColorRange(50, 75, QColor(255, 255, 0));
    ColorRange high = ColorRange(75, 100, QColor(255, 0, 0));

    ColorRangeList emptyList = ColorRangeList({});
    ColorRangeList list = ColorRangeList({low, mid, high});
};

TEST_F(ColorRangeTests, TestEmptyList) {
    EXPECT_THROW((void)emptyList.getColor(0), std::runtime_error);
    EXPECT_THROW((void)emptyList.getColor(50), std::runtime_error);
    EXPECT_THROW((void)emptyList.getColor(69), std::runtime_error);
    EXPECT_THROW((void)emptyList.getColor(100), std::runtime_error);
}

TEST_F(ColorRangeTests, TestNormalValues) {
    EXPECT_EQ(list.getColor(25), QColor(255, 255, 255));
    EXPECT_EQ(list.getColor(60), QColor(255, 255, 0));
    EXPECT_EQ(list.getColor(80), QColor(255, 0, 0));
}

TEST_F(ColorRangeTests, TestEdgeCases) {
    EXPECT_EQ(list.getColor(0), QColor(255, 255, 255));
    EXPECT_EQ(list.getColor(50), QColor(255, 255, 0));
    EXPECT_EQ(list.getColor(75), QColor(255, 0, 0));
    EXPECT_EQ(list.getColor(100), QColor(255, 0, 0));
}

TEST_F(ColorRangeTests, TestOutOfBounds) {
    EXPECT_EQ(list.getColor(-69), QColor(255, 255, 255));
    EXPECT_EQ(list.getColor(169), QColor(255, 0, 0));
}
