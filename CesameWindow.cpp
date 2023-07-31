#include "CesameWindow.h"
#include <iostream>
#include <qtimer.h>

using namespace Cesame;

CesameWindow::CesameWindow(QWidget *parent)
    : QWidget{parent}
{
    mon = new Monitor();

    timer = new QTimer(this);
    // What in the world even is this syntax? Anyway it makes sure the window updates every frameTime;
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&CesameWindow::update));

    timer->start(frameTime);

    // Hacky workaround to get a translucent dark background, not just transparent
    background = new QWidget(this);
    background->lower();
    background->setFixedSize(this->size());

    setStyleSheet("background-color: rgba(14, 16, 24, 128);");
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_TintedBackground, true); // TODO: Look into that, probably does nothing.
    setAttribute(Qt::WA_StyledBackground, true);

    update();
}

void CesameWindow::update()
{
    mon->update();
}

void CesameWindow::resizeEvent(QResizeEvent *event)
{
    background->setFixedSize(this->size());
}
