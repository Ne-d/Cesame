#include "MainWindow.h"

#include <QLabel>

namespace Cesame {
MainWindow::MainWindow() : mainWidget(new MainWidget()) {
    setWindowTitle("Cesame");

    setCentralWidget(mainWidget);
}
} // Cesame
