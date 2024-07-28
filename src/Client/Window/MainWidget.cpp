#include "MainWidget.h"

#include <QStyle>
#include <QBoxLayout>

#include "Bar.h"
#include "CpuCoresBarGraph.h"
#include "Label.h"
#include "LineGraph.h"

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
    auto* cpuUsageLabel = new Label(this, {"CPU Usage: ", MetricType(CpuUsageRateAverage), "%"});
    cpuBox->addWidget(cpuUsageLabel);

    auto* cpuTempLabel = new Label(this, {"CPU Temperature: ", MetricType(CpuTemperaturePackage), "°C"});
    cpuBox->addWidget(cpuTempLabel);

    auto* cpuPowerLabel = new Label(this, {"CPU Power: ??.?? W"});
    cpuBox->addWidget(cpuPowerLabel);

    auto* cpuClockLabel = new Label(this, {"CPU Clock: ", MetricType(CpuClockSpeedAverage), " MHz"});
    cpuBox->addWidget(cpuClockLabel);

    auto* cpuCoresBarGraph = new CpuCoresBarGraph;
    cpuBox->addWidget(cpuCoresBarGraph);

    // GPU
    auto* gpuUsageLabel = new Label(this, {"GPU Usage: ", MetricType(GpuUsageRate), "%"});
    gpuBox->addWidget(gpuUsageLabel);

    auto* gpuTempLabel = new Label(this, {"GPU Temperature: ", MetricType(GpuTemperature), "°C"});
    gpuBox->addWidget(gpuTempLabel);

    auto* gpuPowerLabel = new Label(this, {"GPU Power: ", MetricType(GpuPowerUsage), " W"});
    gpuBox->addWidget(gpuPowerLabel);

    auto* gpuClockLabel = new Label(this, {"GPU Clock: ", MetricType(GpuClockGraphicsCurrent), " MHz"});
    gpuBox->addWidget(gpuClockLabel);

    auto* gpuMemoryLabel = new Label(this, {
                                         "VRAM Used: ", MetricType(GpuMemoryUsed), " GB out of ",
                                         MetricType(GpuMemoryTotal), " GB"
                                     });
    gpuBox->addWidget(gpuMemoryLabel);

    // Memory
    auto* memoryLabel = new Label(this, {
                                      "Memory Used: ", MetricType(MemoryUsed), " GB out of ",
                                      MetricType(MemoryTotal), " GB"
                                  });
    gpuBox->addWidget(memoryLabel);
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
