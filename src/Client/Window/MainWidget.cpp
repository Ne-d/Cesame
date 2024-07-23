#include "MainWidget.h"

#include <QStyle>
#include <QBoxLayout>

#include "Label.h"

namespace Cesame {
MainWidget::MainWidget() {
    // TODO: Use proper styling.
    setStyleSheet("background-color: #00000000");

    // Margins
    constexpr unsigned int margins = 40;
    setContentsMargins(QMargins(margins, margins, margins, margins));

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

    auto* cpuGrid = new QGridLayout;

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

    QList<Label*> cpuGridLabels;
    for (int i = 0; i < 16; i++) {
        auto* label = new Label(this, {
                                    QString::fromStdString(std::to_string(i + 1)), ": ",
                                    MetricType(CpuUsageRatePerCore, i + 1), "%"
                                });
        cpuGridLabels.push_back(label);

        cpuGrid->addWidget(cpuGridLabels.at(i), i / 8, i % 8);
    }
    cpuBox->addLayout(cpuGrid);

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
}
