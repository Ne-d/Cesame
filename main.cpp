// OPEN CESAME (fiat lux mais en moins classe)

// Standard library
#include <iostream>

// Qt
#include <QApplication>
#include <QtWidgets>

// Custom Widgets
#include "cesamewindow.h"
#include "cesamelinegraph.h"
#include "cesamecpucoregraph.h"

// Misc.
#include "utils.h"

void setupLayouts(CesameWindow* window)
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, window);
    QBoxLayout *cpuLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *gpuLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *sideLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    window->setLayout(mainLayout);
    mainLayout->addLayout(cpuLayout);
    mainLayout->addLayout(gpuLayout);
    mainLayout->addLayout(sideLayout);

    // CPU Graphs

    CesameLineGraphSettings cpuUsageSettings;
    cpuUsageSettings.maxValue = 100;
    cpuUsageSettings.alarmValue = 90;
    cpuUsageSettings.criticalValue = 95;
    cpuUsageSettings.prefix = "CPU Usage: ";
    cpuUsageSettings.postfix = " %";
    CesameLineGraph *cpuUsageLineGraph = new CesameLineGraph(window, &(window->cpuMon->usagePerCore.at(0)), cpuUsageSettings);

    CesameLineGraphSettings cpuTempSettings;
    cpuTempSettings.maxValue = 105;
    cpuTempSettings.alarmValue = 95;
    cpuTempSettings.criticalValue = 100;
    cpuTempSettings.prefix = "CPU Temperature: ";
    cpuTempSettings.postfix = " °C";
    CesameLineGraph *cpuTempLineGraph = new CesameLineGraph(window, &(window->cpuMon->temp), cpuUsageSettings);

    CesameLineGraphSettings cpuPowerSettings;
    cpuPowerSettings.maxValue = 70;
    cpuPowerSettings.alarmValue = 40;
    cpuPowerSettings.criticalValue = 50;
    cpuPowerSettings.prefix = "CPU Power: ";
    cpuPowerSettings.postfix = " W";
    CesameLineGraph *cpuPowerLineGraph = new CesameLineGraph(window, &(window->cpuMon->power), cpuPowerSettings);

    CesameLineGraphSettings cpuClockSettings;
    cpuClockSettings.maxValue = 5000;
    cpuClockSettings.alarmValue = 4000;
    cpuClockSettings.criticalValue = 4500;
    cpuClockSettings.prefix = "CPU Clock: ";
    cpuClockSettings.postfix = " MHz";
    CesameLineGraph *cpuClockLineGraph = new CesameLineGraph(window, &(window->cpuMon->clockSpeeds.at(0)), cpuClockSettings);

    CesameCpuCoreGraph *cpuCoreGraph = new CesameCpuCoreGraph(window);

    cpuLayout->addWidget(cpuUsageLineGraph);
    cpuLayout->addWidget(cpuTempLineGraph);
    cpuLayout->addWidget(cpuPowerLineGraph);
    cpuLayout->addWidget(cpuClockLineGraph);
    cpuLayout->addWidget(cpuCoreGraph);

    // GPU Graphs

    CesameLineGraphSettings gpuUsageSettings;
    gpuUsageSettings.maxValue = 100;
    gpuUsageSettings.alarmValue = 95;
    gpuUsageSettings.criticalValue = 98;
    gpuUsageSettings.prefix = "GPU Usage: ";
    gpuUsageSettings.postfix = " %";
    CesameLineGraph *gpuUsageLineGraph = new CesameLineGraph(window, &(window->gpuMon->usage), gpuUsageSettings);

    CesameLineGraphSettings gpuTempSettings;
    gpuTempSettings.maxValue = 90;
    gpuTempSettings.alarmValue = 80;
    gpuTempSettings.criticalValue = 85;
    gpuTempSettings.prefix = "GPU Temperature: ";
    gpuTempSettings.postfix = " °C";
    CesameLineGraph *gpuTempLineGraph = new CesameLineGraph(window, &(window->gpuMon->temperature), gpuTempSettings);

    CesameLineGraphSettings gpuPowerSettings;
    gpuPowerSettings.maxValue = 150;
    gpuPowerSettings.alarmValue = 120;
    gpuPowerSettings.criticalValue = 130;
    gpuPowerSettings.prefix = "GPU Power: ";
    gpuPowerSettings.postfix = " W";
    CesameLineGraph *gpuPowerLineGraph = new CesameLineGraph(window, &(window->gpuMon->power), gpuPowerSettings);

    CesameLineGraphSettings gpuClockSettings;
    gpuClockSettings.maxValue = 5000;
    gpuClockSettings.alarmValue = 4000;
    gpuClockSettings.criticalValue = 4500;
    gpuClockSettings.prefix = "GPU Clock: ";
    gpuClockSettings.postfix = " MHz";
    CesameLineGraph *gpuClockLineGraph = new CesameLineGraph(window, &(window->gpuMon->clockSpeed), gpuClockSettings);

    gpuLayout->addWidget(gpuUsageLineGraph);
    gpuLayout->addWidget(gpuTempLineGraph);
    gpuLayout->addWidget(gpuPowerLineGraph);
    gpuLayout->addWidget(gpuClockLineGraph);

    // Side Graphs

    CesameLineGraphSettings ramUsageSettings;
    gpuClockSettings.maxValue = window->memoryMon->totalMemoryGb;
    gpuClockSettings.alarmValue = 14;
    gpuClockSettings.criticalValue = 15;
    gpuClockSettings.prefix = "RAM Usage: ";
    gpuClockSettings.postfix = " GB";
    CesameLineGraph *ramUsageLineGraph = new CesameLineGraph(window, &(window->memoryMon->usedMemoryGb), ramUsageSettings);
    printf("%f\n", window->memoryMon->usedMemoryGb);

    CesameLineGraphSettings vramUsageSettings;
    gpuClockSettings.maxValue = window->gpuMon->totalVRAM;
    gpuClockSettings.alarmValue = 6;
    gpuClockSettings.criticalValue = 7;
    gpuClockSettings.prefix = "VRAM Usage: ";
    gpuClockSettings.postfix = " GB";
    CesameLineGraph *vramUsageLineGraph = new CesameLineGraph(window, &(window->gpuMon->usedVRAM), vramUsageSettings);

    sideLayout->addWidget(ramUsageLineGraph);
    sideLayout->addWidget(vramUsageLineGraph);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Window and layout creation
    CesameWindow *window = new CesameWindow(nullptr);
    window->update();

    window->setWindowTitle(QApplication::translate("windowTitle", "Cesame"));
    window->show();

    setupLayouts(window);

    return app.exec();
}
