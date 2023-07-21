#ifndef CPUCOREGRAPH_H
#define CPUCOREGRAPH_H

#include <QWidget>
#include "BarGraph.h"
#include "CesameWindow.h"
#include "qgridlayout.h"

namespace Cesame
{

class CpuCoreGraph : public QWidget
{
    Q_OBJECT
public:
    CpuCoreGraph(CesameWindow *parent, Cesame::ColorList inColorList);
    void updateData();

signals:

private:
    QGridLayout* grid;

    QMargins margins;

    double width;
    double height;

    double horizontalSpacing = 20;
    double verticalSpacing = 20;

    unsigned int coreCount;
    unsigned int lines;

    std::vector<double> usagePerCore;

    QList<Cesame::BarGraph*> barGraphList;

    QColor color;

    Cesame::CpuMonitor* cpuMon;
};

}

#endif // CPUCOREGRAPH_H
