#include <QApplication>

#include "GpuMonitor.h"
#include "Window/MainWindow.h"

using namespace Cesame;


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    GpuMonitor mon(0);

    return QApplication::exec();
}
