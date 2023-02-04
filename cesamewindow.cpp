#include "cesamewindow.h"
#include <iostream>
#include <qtimer.h>

CesameWindow::CesameWindow(QWidget *parent)
    : QWidget{parent}
{
    cpuMon = new cpuMonitor();
    memoryMon = new memoryMonitor();
    gpuMon = new gpuMonitor(0);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CesameWindow::update));
    // What in the world even is this syntax? Anyway it makes sure the window updates every frameTime;

    timer->start(frameTime);

    update();
}

void CesameWindow::update()
{
    cpuMon->update();
    memoryMon->update();
    gpuMon->update();
}
