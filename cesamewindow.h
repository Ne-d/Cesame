#ifndef CESAMEWINDOW_H
#define CESAMEWINDOW_H

// Qt Includes
#include <QWidget>
#include "qtimer.h"

// Cesame monitoring includes
#include "cpumonitor.h"
#include "memorymonitor.h"
#include "gpumonitor.h"

class CesameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CesameWindow(QWidget *parent = nullptr);

    cpuMonitor *cpuMon;
    memoryMonitor *memoryMon;
    gpuMonitor *gpuMon;
    QTimer *timer;

public slots:
    void update();

signals:

private:

    int frameTime = 1000;
};

#endif // CESAMEWINDOW_H
