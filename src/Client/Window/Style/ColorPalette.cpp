#include "ColorPalette.h"

#include <utility>

namespace Cesame {
ColorPalette::ColorPalette(std::map<std::string, QColor> colors) : colors(std::move(colors)) {}

QColor ColorPalette::getColor(const std::string& colorName) const {
    if (colors.contains(colorName))
        return colors.at(colorName);

    throw std::invalid_argument("ColorPalette::getColor: Invalid color name");
}

void ColorPalette::addColor(const std::string& colorName, const QColor& color) {
    (void)colors.insert_or_assign(colorName, color);
}
} // Cesame
