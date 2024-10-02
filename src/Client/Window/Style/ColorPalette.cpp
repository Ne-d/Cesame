#include "ColorPalette.h"

namespace Cesame {
std::optional<QColor> ColorPalette::getColor(const std::string& colorName) const {
    return std::make_optional(colors.at(colorName));
}

void ColorPalette::addColor(const std::string& colorName, const QColor& color) {
    (void)colors.insert_or_assign(colorName, color);
}
} // Cesame
