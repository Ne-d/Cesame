#ifndef CESAMEWINDOW_H
#define CESAMEWINDOW_H

// Qt Includes
#include <QWidget>
#include "qtimer.h"

// Cesame monitoring includes
#include "CpuMonitor.h"
#include "MemoryMonitor.h"
#include "GpuMonitor.h"
#include "NetworkMonitor.h"

class CesameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CesameWindow(QWidget *parent = nullptr);

    Cesame::CpuMonitor *cpuMon;
    Cesame::MemoryMonitor *memoryMon;
    Cesame::GpuMonitor *gpuMon;
    Cesame::NetworkMonitor *networkMon;

    QTimer *timer;

public slots:
    void update();
    void resizeEvent(QResizeEvent *event) override;

signals:

private:
    QWidget *background;
    int frameTime = 1000;
};

#endif // CESAMEWINDOW_H
