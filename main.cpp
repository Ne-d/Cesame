// OPEN CESAME (fiat lux mais en moins classe)

// Standard library
#include <iostream>
#include <fmt/core.h>

// Qt
#include <QApplication>
#include <QtWidgets>

// Custom Widgets
#include "CesameWindow.h"
#include "Label.h"
#include "LineGraph.h"
#include "CpuCoreGraph.h"

using namespace Cesame;

void setupLayouts(CesameWindow* window)
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, window);
    QBoxLayout *cpuLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *gpuLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *sideLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    int spacing = 30;

    window->setLayout(mainLayout);
    mainLayout->addLayout(cpuLayout);
    mainLayout->addLayout(gpuLayout);
    mainLayout->addLayout(sideLayout);

    mainLayout->setSpacing(spacing);
    cpuLayout->setSpacing(spacing);
    gpuLayout->setSpacing(spacing);
    sideLayout->setSpacing(spacing);

    mainLayout->setContentsMargins(QMargins(spacing, spacing, spacing, spacing));

    // CPU Graphs

    LineGraphSettings cpuUsageSettings;
    cpuUsageSettings.maxValue = 100;
    cpuUsageSettings.alarmValue = 90;
    cpuUsageSettings.criticalValue = 95;
    LineGraphText *cpuUsageLineGraph = new LineGraphText(window, &(window->cpuMon->usagePerCore.at(0)), cpuUsageSettings);
    *cpuUsageLineGraph->label << "CPU usage: " << &window->cpuMon->usagePerCore.at(0) << "%";

    LineGraphSettings cpuTempSettings;
    cpuTempSettings.maxValue = 105;
    cpuTempSettings.alarmValue = 95;
    cpuTempSettings.criticalValue = 100;
    LineGraphText *cpuTempLineGraph = new LineGraphText(window, &(window->cpuMon->temp), cpuTempSettings);
    *cpuTempLineGraph->label << "CPU temperature: " << &(window->cpuMon->temp) << "°C";

    LineGraphSettings cpuPowerSettings;
    cpuPowerSettings.maxValue = 70;
    cpuPowerSettings.alarmValue = 40;
    cpuPowerSettings.criticalValue = 50;
    LineGraphText *cpuPowerLineGraph = new LineGraphText(window, &(window->cpuMon->power), cpuPowerSettings);
    *cpuPowerLineGraph->label << "CPU power: " << &(window->cpuMon->power) << " W";

    LineGraphSettings cpuClockSettings;
    cpuClockSettings.maxValue = 5000;
    cpuClockSettings.alarmValue = 4000;
    cpuClockSettings.criticalValue = 4500;
    LineGraphText *cpuClockLineGraph = new LineGraphText(window, &(window->cpuMon->clockSpeeds.at(0)), cpuClockSettings);
    *cpuClockLineGraph->label << "CPU Clock: " << &(window->cpuMon->clockSpeeds.at(0)) << " MHz"; // TODO: Should be an average of all cores.

    ColorList cpuCoreColorList;
    cpuCoreColorList << ColorRange(0, 85, CESAME_COLOR_DEFAULT)
                     << ColorRange(85, 95, CESAME_COLOR_ALARM)
                     << ColorRange(95, 100, CESAME_COLOR_CRITICAL);
    CpuCoreGraph* cpuCoreGraph = new CpuCoreGraph(window, cpuCoreColorList);

    cpuLayout->addLayout(cpuUsageLineGraph);
    cpuLayout->addLayout(cpuTempLineGraph);
    cpuLayout->addLayout(cpuPowerLineGraph);
    cpuLayout->addLayout(cpuClockLineGraph);
    cpuLayout->addWidget(cpuCoreGraph);

    // GPU Graphs

    LineGraphSettings gpuUsageSettings;
    gpuUsageSettings.maxValue = 100;
    gpuUsageSettings.alarmValue = 95;
    gpuUsageSettings.criticalValue = 98;
    LineGraphText *gpuUsageLineGraph = new LineGraphText(window, &(window->gpuMon->usage), gpuUsageSettings);
    *gpuUsageLineGraph->label << "GPU Usage: " << &(window->gpuMon->usage) << "%";

    LineGraphSettings gpuTempSettings;
    gpuTempSettings.maxValue = 90;
    gpuTempSettings.alarmValue = 80;
    gpuTempSettings.criticalValue = 85;
    LineGraphText *gpuTempLineGraph = new LineGraphText(window, &(window->gpuMon->temperature), gpuTempSettings);
    *gpuTempLineGraph->label << "GPU Temperature: " << &(window->gpuMon->temperature) << "°C";

    LineGraphSettings gpuPowerSettings;
    gpuPowerSettings.maxValue = 150;
    gpuPowerSettings.alarmValue = 120;
    gpuPowerSettings.criticalValue = 130;
    LineGraphText *gpuPowerLineGraph = new LineGraphText(window, &(window->gpuMon->power), gpuPowerSettings);
    *gpuPowerLineGraph->label << "GPU Power: " << &(window->gpuMon->power) << " W";

    LineGraphSettings gpuClockSettings;
    gpuClockSettings.maxValue = 5000;
    gpuClockSettings.alarmValue = 4000;
    gpuClockSettings.criticalValue = 4500;
    LineGraphText *gpuClockLineGraph = new LineGraphText(window, &(window->gpuMon->clockSpeed), gpuClockSettings);
    *gpuClockLineGraph->label << "GPU Clock: " << &(window->gpuMon->clockSpeed) << " MHz";

    LineGraphSettings vramUsageSettings;
    vramUsageSettings.maxValue = window->gpuMon->totalVRAM;
    vramUsageSettings.alarmValue = 6;
    vramUsageSettings.criticalValue = 7;
    LineGraphText *vramUsageLineGraph = new LineGraphText(window, &(window->gpuMon->usedVRAM), vramUsageSettings);
    *vramUsageLineGraph->label << "VRAM Usage: " << &(window->gpuMon->usedVRAM) << " GB";

    gpuLayout->addLayout(gpuUsageLineGraph);
    gpuLayout->addLayout(gpuTempLineGraph);
    gpuLayout->addLayout(gpuPowerLineGraph);
    gpuLayout->addLayout(gpuClockLineGraph);
    gpuLayout->addLayout(vramUsageLineGraph);

    // Side Graphs

    LineGraphSettings ramUsageSettings;
    ramUsageSettings.maxValue = window->memoryMon->totalMemoryGb;
    ramUsageSettings.alarmValue = 24;
    ramUsageSettings.criticalValue = 30;
    LineGraphText *ramUsageLineGraph = new LineGraphText(window, &(window->memoryMon->usedMemoryGb), ramUsageSettings);
    *ramUsageLineGraph->label << "RAM Usage: " << &(window->memoryMon->usedMemoryGb) << " GB";

    LineGraphSettings pingSettings;
    pingSettings.maxValue = 100;
    pingSettings.alarmValue = 50;
    pingSettings.criticalValue = 100;
    LineGraphText *pingLineGraph = new LineGraphText(window, &(window->networkMon->ping), pingSettings);
    *pingLineGraph->label << "Router ping: " << &(window->networkMon->ping) << " ms" << ", chokes: " << &(window->networkMon->lossCounter);

    sideLayout->addLayout(ramUsageLineGraph);
    sideLayout->addLayout(pingLineGraph);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CesameWindow *window = new CesameWindow(nullptr);

    window->setWindowTitle(QApplication::translate("windowTitle", "Cesame"));
    window->show();

    setupLayouts(window);

    return app.exec();
}
