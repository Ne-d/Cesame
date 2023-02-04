#ifndef CESAMECPUCOREGRAPH_H
#define CESAMECPUCOREGRAPH_H

#include <QWidget>
#include "cesamewindow.h"

#define COLOR_WHITE QColor(255, 255, 255, 255)

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
    QMargins margins;

    double width;
    double height;

    double horizontalSpacing;
    double verticalSpacing;

    int lines;

    QColor color;

    cpuMonitor* cpuMon;
};

#endif // CESAMECPUCOREGRAPH_H
