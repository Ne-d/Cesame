// OPEN CESAME (fiat lux mais en moins classe)

// Standard library
#include <iostream>

// Qt
#include <QApplication>
#include <QtWidgets>

// Project files
#include "CesameWindow.h"
#include "CpuCoreGraph.h"
#include "LineGraph.h"
#include "MetricsManager.h"
#include "MonitorTypes.h"

#include <boost/interprocess/mapped_region.hpp>

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
    MetricDefinition cpuUsageDef = mDef(CPUUsageAverage, Percent, 0);
    LineGraphText *cpuUsageLineGraph = new LineGraphText(window, cpuUsageDef, cpuUsageSettings);
    *cpuUsageLineGraph->label << "CPU usage: " << cpuUsageDef << "%";

    LineGraphSettings cpuTempSettings;
    cpuTempSettings.maxValue = 105;
    cpuTempSettings.alarmValue = 95;
    cpuTempSettings.criticalValue = 100;
    MetricDefinition cpuTempDef = mDef(CPUTemperaturePackage, Celsius, 0);
    LineGraphText *cpuTempLineGraph = new LineGraphText(window, cpuTempDef, cpuTempSettings);
    *cpuTempLineGraph->label << "CPU temperature: " << cpuTempDef << "°C";

    LineGraphSettings cpuPowerSettings;
    cpuPowerSettings.maxValue = 70;
    cpuPowerSettings.alarmValue = 40;
    cpuPowerSettings.criticalValue = 50;
    MetricDefinition cpuPowerDef = mDef(CPUPowerPackage, Watt, 0);
    LineGraphText *cpuPowerLineGraph = new LineGraphText(window, cpuPowerDef, cpuPowerSettings);
    *cpuPowerLineGraph->label << "CPU power: " << cpuPowerDef << " W";

    LineGraphSettings cpuClockSettings;
    cpuClockSettings.maxValue = 5000;
    cpuClockSettings.alarmValue = 4000;
    cpuClockSettings.criticalValue = 4500;
    MetricDefinition cpuClockDef = mDef(Cesame::CPUClockAverage, Megahertz, 0);
    LineGraphText *cpuClockLineGraph = new LineGraphText(window, cpuClockDef, cpuClockSettings);
    *cpuClockLineGraph->label << "CPU Clock: " << cpuClockDef << " MHz"; // TODO: Should be an average of all cores.

    ColorList cpuCoreColorList;
    cpuCoreColorList << ColorRange(0, 85, CESAME_COLOR_DEFAULT)
                     << ColorRange(85, 95, CESAME_COLOR_ALARM)
                     << ColorRange(95, 100, CESAME_COLOR_CRITICAL);
    CpuCoreGraph* cpuCoreGraph = new CpuCoreGraph(window, cpuCoreColorList);


    cpuLayout->addWidget(cpuUsageLineGraph);
    cpuLayout->addWidget(cpuTempLineGraph);
    cpuLayout->addWidget(cpuPowerLineGraph);
    cpuLayout->addWidget(cpuClockLineGraph);
    cpuLayout->addWidget(cpuCoreGraph);

    // GPU Graphs

    LineGraphSettings gpuUsageSettings;
    gpuUsageSettings.maxValue = 100;
    gpuUsageSettings.alarmValue = 95;
    gpuUsageSettings.criticalValue = 98;
    MetricDefinition gpuUsageDef = mDef(GPUUsage, Percent, 0);
    LineGraphText *gpuUsageLineGraph = new LineGraphText(window, gpuUsageDef, gpuUsageSettings);
    *gpuUsageLineGraph->label << "GPU Usage: " << gpuUsageDef << "%";

    LineGraphSettings gpuTempSettings;
    gpuTempSettings.maxValue = 90;
    gpuTempSettings.alarmValue = 80;
    gpuTempSettings.criticalValue = 85;
    MetricDefinition gpuTempDef = mDef(GPUTemperature, Celsius, 0);
    LineGraphText *gpuTempLineGraph = new LineGraphText(window, gpuTempDef, gpuTempSettings);
    *gpuTempLineGraph->label << "GPU Temperature: " << gpuTempDef << "°C";

    LineGraphSettings gpuPowerSettings;
    gpuPowerSettings.maxValue = 150;
    gpuPowerSettings.alarmValue = 120;
    gpuPowerSettings.criticalValue = 130;
    MetricDefinition gpuPowerDef = mDef(GPUPower, Watt, 0);
    LineGraphText *gpuPowerLineGraph = new LineGraphText(window, gpuPowerDef, gpuPowerSettings);
    *gpuPowerLineGraph->label << "GPU Power: " << gpuPowerDef << " W";

    LineGraphSettings gpuClockSettings;
    gpuClockSettings.maxValue = 5000;
    gpuClockSettings.alarmValue = 4000;
    gpuClockSettings.criticalValue = 4500;
    MetricDefinition gpuClockDef = mDef(GPUClock, Megahertz, 0);
    LineGraphText *gpuClockLineGraph = new LineGraphText(window, gpuClockDef, gpuClockSettings);
    *gpuClockLineGraph->label << "GPU Clock: " << gpuClockDef << " MHz";


    LineGraphSettings vramUsageSettings;
    vramUsageSettings.maxValue = std::get<double>(MetricsManager::getMetric(VRAMTotal, Gigabyte, 0));
    vramUsageSettings.alarmValue = 6;
    vramUsageSettings.criticalValue = 7;
    MetricDefinition vramUsageDef = mDef(VRAMUsed, Gigabyte, 0);
    LineGraphText *vramUsageLineGraph = new LineGraphText(window, vramUsageDef, vramUsageSettings);
    *vramUsageLineGraph->label << "VRAM Usage: " << vramUsageDef << " GB";


    gpuLayout->addWidget(gpuUsageLineGraph);
    gpuLayout->addWidget(gpuTempLineGraph);
    gpuLayout->addWidget(gpuPowerLineGraph);
    gpuLayout->addWidget(gpuClockLineGraph);
    gpuLayout->addWidget(vramUsageLineGraph);

    // Side Graphs
    /*
    // TODO: This crashes the program and puts the IPC communication or the server into a bad state.
    LineGraphSettings ramUsageSettings;
    ramUsageSettings.maxValue = std::get<double>(MetricsManager::getMetric(RAMTotal, Gigabyte, 0));
    ramUsageSettings.alarmValue = 24;
    ramUsageSettings.criticalValue = 30;
    MetricDefinition ramUsageDef = mDef(Cesame::RAMUsed, Gigabyte, 0);
    LineGraphText *ramUsageLineGraph = new LineGraphText(window, ramUsageDef, ramUsageSettings);
    *ramUsageLineGraph->label << "RAM Usage: " << ramUsageDef << " GB";

    sideLayout->addWidget(ramUsageLineGraph);
*/

}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CesameWindow *window = new CesameWindow(nullptr);

    MetricsManager::init();

    window->setWindowTitle(QApplication::translate("windowTitle", "Cesame"));
    setupLayouts(window);
    window->show();

    return app.exec();
}
