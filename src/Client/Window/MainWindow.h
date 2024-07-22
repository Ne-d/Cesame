#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MainWidget.h"

namespace Cesame {
class MainWindow final : public QMainWindow {
public:
    MainWindow();

private:
    MainWidget* mainWidget;
};
} // Cesame

#endif //MAINWINDOW_H
