#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <map>
#include <optional>
#include <string>

#include <QColor>

namespace Cesame {
class ColorPalette {
public:
    explicit ColorPalette() = default;
    explicit ColorPalette(std::map<std::string, QColor> colors);

    [[nodiscard]] std::optional<QColor> getColor(const std::string& colorName) const;
    void addColor(const std::string& colorName, const QColor& color);

private:
    std::map<std::string, QColor> colors{};
};
} // Cesame

#endif //COLORPALETTE_H
