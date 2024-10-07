#include "StyleManager.h"

namespace Cesame {
StyleManager& StyleManager::getInstance() {
    static StyleManager instance;
    return instance;
}

ColorPalette StyleManager::getDefaultPalette() const {
    return defaultPalette;
}

void StyleManager::setDefaultPalette(const ColorPalette& defaultPalette) {
    this->defaultPalette = defaultPalette;
}
} // Cesame
