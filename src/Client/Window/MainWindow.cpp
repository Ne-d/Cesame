#include "MainWindow.h"

#include <QLabel>

#include "Style/StyleManager.h"

namespace Cesame {
MainWindow::MainWindow() {
    setWindowTitle("Cesame");

    // Setup style

    // Nord Color Palette
    const ColorPalette palette({
        // Polar Night
        {"grey0", "#2e3440"},
        {"grey1", "#3b4252"},
        {"grey2", "#434c5e"},
        {"grey3", "#4c566a"},

        // Snow Storm
        {"white4", "#d8dee9"},
        {"white5", "#e5e9f0"},
        {"white6", "#eceff4"},

        // Frost
        {"frost7", "#8fbcbb"},
        {"frost8", "#88c0d0"},
        {"frost9", "#81a1c1"},
        {"frost10", "#5e81ac"},

        // Aurora
        {"red", "#bf616a"},
        {"orange", "#d08770"},
        {"yellow", "#ebcb8b"},
        {"green", "#a3be8c"},
        {"purple", "#b48ead"}
    });

    StyleManager::getInstance().setDefaultPalette(palette);

    mainWidget = new MainWidget;

    setCentralWidget(mainWidget);
}
} // Cesame
