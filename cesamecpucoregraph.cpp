#include "cesamecpucoregraph.h"
#include "cesamebargraph.h"
#include "utils.h"

CesameCpuCoreGraph::CesameCpuCoreGraph(CesameWindow *parent): QWidget{parent}
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CesameCpuCoreGraph::updateData));

    cpuMon = parent->cpuMon;
    coreCount = cpuMon->coreCount;

    margins = QMargins(10, 10, 10, 10);
    color = COLOR_WHITE;
    lines = 2;

    grid = new QGridLayout(this);

    grid->setHorizontalSpacing(horizontalSpacing);
    grid->setVerticalSpacing(verticalSpacing);

    CesameBarGraphSettings barGraphSettings;
    barGraphSettings.maxValue = 100;

    for(unsigned int i = 0; i < coreCount;i++)
    {
        barGraphList << new CesameBarGraph(this, barGraphSettings);
        grid->addWidget(barGraphList.at(i), i / (coreCount / lines), i % (coreCount / lines));
    }
}

void CesameCpuCoreGraph::updateData()
{
    usagePerCore = cpuMon->usagePerCore;

    for(unsigned int i = 0; i < coreCount; i++)
    {
       barGraphList.at(i)->setValue(cpuMon->usagePerCore.at(i));
       barGraphList.at(i)->update();
    }
}

void CesameCpuCoreGraph::paintEvent(QPaintEvent *event)
{
    /*
    QPainter painter(this);

    QPen pen;

    // Setting up QPen and QPainter parameters
    pen.setColor(color);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(LINE_WIDTH);
    painter.setPen(pen);

    */
}
