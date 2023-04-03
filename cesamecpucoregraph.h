#ifndef CESAMECPUCOREGRAPH_H
#define CESAMECPUCOREGRAPH_H

#include <QWidget>
#include "cesamebargraph.h"
#include "cesamewindow.h"
#include "qgridlayout.h"

class CesameCpuCoreGraph : public QWidget
{
    Q_OBJECT
public:
    CesameCpuCoreGraph(CesameWindow *parent = nullptr);
    void updateData();

public slots:
    void paintEvent(QPaintEvent *event);

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

    QList<CesameBarGraph*> barGraphList;

    QColor color;

    cpuMonitor* cpuMon;
};

#endif // CESAMECPUCOREGRAPH_H
