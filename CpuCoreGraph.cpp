#include "CpuCoreGraph.h"
#include "BarGraph.h"
#include "Color.h"
#include "MetricsManager.h"

using namespace Cesame;

CpuCoreGraph::CpuCoreGraph(CesameWindow *parent, ColorList inColorList): QWidget{parent}
{
    // Setting up the automatic refresh based on the parent CesameWindow's timer.
    connect(parent->timer, &QTimer::timeout, this, QOverload<>::of(&CpuCoreGraph::updateData));

    coreCount = std::get<int>(MetricsManager::getMetric(CPUCoreCount));

    margins = QMargins(0, 0, 0, 0); //QMargins(10, 10, 10, 10);
    color = CESAME_COLOR_DEFAULT;
    lines = 2;

    grid = new QGridLayout(this);

    grid->setContentsMargins(margins);
    grid->setHorizontalSpacing(horizontalSpacing);
    grid->setVerticalSpacing(verticalSpacing);

    for(unsigned int i = 0; i < coreCount; i++) // For each core of the CPU
    {
        // Create a bar graph, and add it to the list
        barGraphList << new BarGraph(this, 100, inColorList);

        // Add the new graph to the grid, on the correct line
        grid->addWidget(barGraphList.at(i),
            i / (coreCount / lines),
            i % (coreCount / lines));
    }
}

void CpuCoreGraph::updateData()
{
    for(unsigned int i = 0; i < coreCount; i++)
    {
        double val = std::get<int>(MetricsManager::getMetric(CPUUsageCore, Percent, i));
        barGraphList.at(i)->setValue(val);
        barGraphList.at(i)->update();
    }
}
