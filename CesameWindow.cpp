#include "CesameWindow.h"
#include <iostream>
#include <qtimer.h>

using namespace Cesame;

CesameWindow::CesameWindow(QWidget *parent)
    : QWidget{parent}
{
    cpuMon = new CpuMonitor();
    memoryMon = new MemoryMonitor();
    gpuMon = new GpuMonitor(0);
    networkMon = new NetworkMonitor();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CesameWindow::update));
    // What in the world even is this syntax? Anyway it makes sure the window updates every frameTime;

    timer->start(frameTime);

    background = new QWidget(this);
    background->lower();
    background->setFixedSize(this->size());

    setStyleSheet("background-color: rgba(14, 16, 24, 128);");
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TintedBackground, true);
    setAttribute(Qt::WA_StyledBackground, true);

    update();
}

void CesameWindow::update()
{
    cpuMon->update();
    memoryMon->update();
    gpuMon->update();
    networkMon->update();
}

void CesameWindow::resizeEvent(QResizeEvent *event)
{
    background->setFixedSize(this->size());
}
