#include "MainWindow.h"

#include <QLabel>

namespace Cesame {
MainWindow::MainWindow() : mainWidget(new MainWidget()) {
    setWindowTitle("Cesame");

    setCentralWidget(mainWidget);
    //auto* label = new QLabel("Hello there!", this);
    //setCentralWidget(label);
}
} // Cesame
