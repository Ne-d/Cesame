#include "MainWidget.h"

#include "Bar.h"
#include "CpuCoresBarGraph.h"
#include "Label.h"
#include "LineGraph.h"
#include "LineGraphLabeled.h"

namespace Cesame {
MainWidget::MainWidget() {
    // TODO: Use proper styling.
    setStyleSheet("background-color: #00000000");

    // Margins
    constexpr unsigned int margins = 40;
    setContentsMargins(QMargins(margins, margins, margins, margins));

    setupMainDemo();
}

void MainWidget::setupMainDemo() {
    constexpr unsigned int nbDataPoints = 300;

    // Layouts
    auto* mainBox = new QHBoxLayout;
    setLayout(mainBox);
    mainBox->setSpacing(40);

    auto* cpuBox = new QVBoxLayout;
    mainBox->addLayout(cpuBox);

    auto* gpuBox = new QVBoxLayout;
    mainBox->addLayout(gpuBox);

    auto* miscBox = new QVBoxLayout;
    mainBox->addLayout(miscBox);

    // Labels
    // CPU
    auto* cpuUsageGraph = new LineGraphLabeled({{CpuUsageRateAverage, 100}}, nbDataPoints,
                                               {"CPU Usage: ", CpuUsageRateAverage, "%"});
    cpuBox->addWidget(cpuUsageGraph);

    auto* cpuTempGraph = new LineGraphLabeled({{CpuTemperaturePackage, 105}}, nbDataPoints,
                                              {"CPU Temperature: ", CpuTemperaturePackage, "°C"});
    cpuBox->addWidget(cpuTempGraph);

    auto* cpuClockGraph = new LineGraphLabeled({{CpuClockSpeedAverage, 5000}}, nbDataPoints,
                                               {"CPU Clock: ", CpuClockSpeedAverage, "MHz"});
    cpuBox->addWidget(cpuClockGraph);

    // Memory
    auto* memoryGraph = new LineGraphLabeled({{MemoryUsed, 32}}, nbDataPoints,
                                             {"Memory Usage: ", MemoryUsed, " GB / ", MemoryTotal, " GB"});
    cpuBox->addWidget(memoryGraph);

    auto* cpuCoresBarGraph = new CpuCoresBarGraph;
    cpuBox->addWidget(cpuCoresBarGraph);


    // GPU
    auto* gpuUsageGraph = new LineGraphLabeled({{GpuUsageRate, 100}}, nbDataPoints,
                                               {"GPU Usage: ", GpuUsageRate, "%"});
    gpuBox->addWidget(gpuUsageGraph);

    auto* gpuTempGraph = new LineGraphLabeled({{GpuTemperature, 86}}, nbDataPoints,
                                              {"GPU Temperature: ", GpuTemperature, "°C"});
    gpuBox->addWidget(gpuTempGraph);

    auto* gpuPowerGraph = new LineGraphLabeled({
                                                   {GpuPowerUsage, 140},
                                                   {GpuEnforcedPowerLimit, 140}
                                               }, nbDataPoints,
                                               {"GPU Power: ", GpuPowerUsage, " W / ", GpuEnforcedPowerLimit, " W"});
    gpuBox->addWidget(gpuPowerGraph);


    auto* gpuClockGraph = new LineGraphLabeled({{GpuClockGraphicsCurrent, 3000}}, nbDataPoints,
                                               {"GPU Clock: ", GpuClockGraphicsCurrent, " MHz"});
    gpuBox->addWidget(gpuClockGraph);

    auto* gpuMemoryGraph = new LineGraphLabeled({{GpuMemoryUsed, 8},}, nbDataPoints,
                                                {"VRAM Usage: ", MemoryUsed, " GB / ", GpuMemoryTotal, " GB"});
    gpuBox->addWidget(gpuMemoryGraph);
}

void MainWidget::setupLineGraphDemo() {
    auto* layout = new QVBoxLayout;

    LineGraphElement elementCpuUsageAverage(MetricType(CpuUsageRateAverage), 100);
    auto* lineGraphCpuUsageAverage = new LineGraph(this, {elementCpuUsageAverage}, 300);
    layout->addWidget(lineGraphCpuUsageAverage);

    LineGraphElement elementGpuPowerCurrent(MetricType(GpuPowerUsage), 150);
    LineGraphElement elementGpuPowerMax(MetricType(GpuEnforcedPowerLimit), 150);
    auto* lineGraphGpuPower = new LineGraph(this, {elementGpuPowerCurrent, elementGpuPowerMax}, 300);
    layout->addWidget(lineGraphGpuPower);

    setLayout(layout);
}
}
