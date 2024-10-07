#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "ColorPalette.h"

namespace Cesame {
/**
 * A singleton that contains style information such as color palettes for the entire program.
 */
class StyleManager {
public:
    // Singleton stuff
    static StyleManager& getInstance();

    StyleManager(const StyleManager&) = delete;
    void operator=(const StyleManager&) = delete;

    // Methods
    [[nodiscard]] ColorPalette getDefaultPalette() const;
    void setDefaultPalette(const ColorPalette& defaultPalette);

private:
    // Singleton stuff
    StyleManager() = default;

    // Data
    ColorPalette defaultPalette;
};
} // Cesame

#endif //STYLEMANAGER_H
