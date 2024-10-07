#include <gtest/gtest.h>

#include "Window/Style/ColorPalette.h"

using namespace Cesame;

class ColorPaletteTests : public testing::Test {
protected:
    const ColorPalette emptyPalette{};
    ColorPalette palette;

    std::map<std::string, QColor> map = {
        {"red", QColor(255, 0, 0)},
        {"green", QColor(0, 255, 0)},
        {"blue", QColor(0, 0, 255)}
    };

    ColorPaletteTests() :
        emptyPalette({}),
        palette({
            {"red", QColor(255, 0, 0)},
            {"green", QColor(0, 255, 0)},
            {"blue", QColor(0, 0, 255)}
        }) {}
};

TEST_F(ColorPaletteTests, TestEmptyPalette) {
    ASSERT_THROW((void)emptyPalette.getColor("something"), std::invalid_argument);
}

TEST_F(ColorPaletteTests, TestExistingColors) {
    ASSERT_EQ(palette.getColor("red"), QColor(255, 0, 0));
    ASSERT_EQ(palette.getColor("green"), QColor(0, 255, 0));
    ASSERT_EQ(palette.getColor("blue"), QColor(0, 0, 255));
}

TEST_F(ColorPaletteTests, TestAddingColors) {
    palette.addColor("nice", QColor(69, 69, 69));
    ASSERT_EQ(palette.getColor("nice"), QColor(69, 69, 69));
}
