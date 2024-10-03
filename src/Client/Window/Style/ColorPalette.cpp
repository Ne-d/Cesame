#include "ColorPalette.h"

#include <utility>

namespace Cesame {
ColorPalette::ColorPalette(std::map<std::string, QColor> colors) : colors(std::move(colors)) {}

std::optional<QColor> ColorPalette::getColor(const std::string& colorName) const {
    if (colors.contains(colorName))
        return std::make_optional(colors.at(colorName));

    return std::nullopt;
}

void ColorPalette::addColor(const std::string& colorName, const QColor& color) {
    (void)colors.insert_or_assign(colorName, color);
}
} // Cesame
