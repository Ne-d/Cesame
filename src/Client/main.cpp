#include <QApplication>

#include "Window/MainWindow.h"

using namespace Cesame;


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    MainWindow window;
    window.show();

    return QApplication::exec();
}
