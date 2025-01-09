#include "MainWidget.h"

#include <QPointer>

#include "Bar.h"
#include "ColorPalette.h"
#include "CpuCoresBarGraph.h"
#include "Label.h"
#include "LineGraph.h"
#include "LineGraphLabeled.h"
#include "StyleManager.h"

namespace Cesame {
MainWidget::MainWidget() {
    // TODO: Use proper styling.
    setStyleSheet("background-color: #00000000");

    // Margins
    constexpr unsigned int margins = 40;
    setContentsMargins(QMargins(margins, margins, margins, margins));

    setupMainDemo();
    //setupDebugDemo();
}

void MainWidget::setupMainDemo() {
    constexpr unsigned int nbDataPoints = 300;

    // Color Palette
    const ColorPalette palette = StyleManager::getInstance().getDefaultPalette();
    const QColor white = palette.getColor("white4");
    const QColor orange = palette.getColor("orange");
    const QColor red = palette.getColor("red");

    // Layouts
    const QPointer mainBox = new QHBoxLayout();
    setLayout(mainBox);
    mainBox->setSpacing(40);

    const QPointer cpuBox = new QVBoxLayout();
    mainBox->addLayout(cpuBox);

    const QPointer gpuBox = new QVBoxLayout();
    mainBox->addLayout(gpuBox);

    const QPointer miscBox = new QVBoxLayout();
    mainBox->addLayout(miscBox);

    // Labels
    // CPU
    ColorRangeList cpuUsageColorRanges({
        {0, 75, white},
        {75, 95, orange},
        {95, 100, red}
    });
    auto* cpuUsageGraph = new LineGraphLabeled({{CpuUsageRateAverage, 100, 0, cpuUsageColorRanges}}, nbDataPoints,
                                               {"CPU Usage: ", CpuUsageRateAverage, "%"}, cpuUsageColorRanges, 1);
    cpuBox->addWidget(cpuUsageGraph);

    ColorRangeList cpuTempColorRanges({
        {0, 90, white},
        {90, 98, orange},
        {98, 105, red}
    });
    auto* cpuTempGraph = new LineGraphLabeled({{CpuTemperaturePackage, 105, 0, cpuTempColorRanges}}, nbDataPoints,
                                              {"CPU Temperature: ", CpuTemperaturePackage, "°C"}, cpuTempColorRanges,
                                              1);
    cpuBox->addWidget(cpuTempGraph);

    ColorRangeList cpuClockColorRanges({});
    auto* cpuClockGraph = new LineGraphLabeled({{CpuClockSpeedAverage, 5000, 0, cpuClockColorRanges}}, nbDataPoints,
                                               {"CPU Clock: ", CpuClockSpeedAverage, "MHz"}, cpuClockColorRanges, 1);
    cpuBox->addWidget(cpuClockGraph);

    // Memory
    ColorRangeList memoryColorRanges({
        {0, 24, white},
        {24, 28, orange},
        {28, 32, red}
    });
    auto* memoryGraph = new LineGraphLabeled({{MemoryUsed, 32, 0, memoryColorRanges}}, nbDataPoints,
                                             {"Memory Usage: ", MemoryUsed, " GB / ", MemoryTotal, " GB"},
                                             memoryColorRanges, 1);
    cpuBox->addWidget(memoryGraph);

    auto* cpuCoresBarGraph = new CpuCoresBarGraph(ColorRangeList({
        {0, 75, palette.getColor("white4")},
        {75, 95, palette.getColor("orange")},
        {95, 100, palette.getColor("red")}
    }));
    cpuBox->addWidget(cpuCoresBarGraph);


    // GPU
    ColorRangeList gpuUsageColorRanges({
        {0, 95, white},
        {95, 98, orange},
        {98, 100, red}
    });
    auto* gpuUsageGraph = new LineGraphLabeled({{GpuUsageRate, 100, 0, gpuUsageColorRanges}}, nbDataPoints,
                                               {"GPU Usage: ", GpuUsageRate, "%"}, gpuUsageColorRanges, 1);
    gpuBox->addWidget(gpuUsageGraph);

    ColorRangeList gpuTempColorRanges({
        {0, 75, white},
        {75, 84, orange},
        {84, 100, red}
    });
    auto* gpuTempGraph = new LineGraphLabeled({{GpuTemperature, 86, 0, gpuTempColorRanges}}, nbDataPoints,
                                              {"GPU Temperature: ", GpuTemperature, "°C"}, gpuTempColorRanges, 1);
    gpuBox->addWidget(gpuTempGraph);

    ColorRangeList gpuPowerColorRanges({
        {0, 115, white},
        {115, 130, orange},
        {130, 150, red}
    });
    ColorRangeList gpuPowerLimitColorRanges({
        {0, 116, white},
        {115, 130, orange},
        {130, 150, red}
    });
    auto* gpuPowerGraph = new LineGraphLabeled({
                                                   {GpuPowerUsage, 140, 0, gpuPowerColorRanges},
                                                   {GpuEnforcedPowerLimit, 140, 0, gpuPowerLimitColorRanges}
                                               }, nbDataPoints,
                                               {"GPU Power: ", GpuPowerUsage, " W / ", GpuEnforcedPowerLimit, " W"},
                                               gpuPowerColorRanges, 1);
    gpuBox->addWidget(gpuPowerGraph);


    ColorRangeList gpuClockColorRanges({
        {0, 2000, white},
        {2000, 2500, orange},
        {2500, 3000, red}
    });
    auto* gpuClockGraph = new LineGraphLabeled({{GpuClockGraphicsCurrent, 3000, 0, gpuClockColorRanges}}, nbDataPoints,
                                               {"GPU Clock: ", GpuClockGraphicsCurrent, " MHz"}, gpuClockColorRanges,
                                               1);
    gpuBox->addWidget(gpuClockGraph);

    ColorRangeList gpuMemoryColorRanges({
        {0, 6, white},
        {6, 7, orange},
        {7, 8, red}
    });
    auto* gpuMemoryGraph = new LineGraphLabeled({{GpuMemoryUsed, 8, 0, gpuMemoryColorRanges}}, nbDataPoints,
                                                {"VRAM Usage: ", GpuMemoryUsed, " GB / ", GpuMemoryTotal, " GB"},
                                                gpuMemoryColorRanges, 1);
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

void MainWidget::setupDebugDemo() {
    auto* layout = new QVBoxLayout();

    int nbDataPoints = 100;

    const ColorPalette palette = StyleManager::getInstance().getDefaultPalette();
    const QColor white = palette.getColor("white4");
    const QColor orange = palette.getColor("orange");
    const QColor red = palette.getColor("red");

    ColorRangeList colorRanges({
        {0, 10, white},
        {10, 70, orange},
        {70, 100, red}
    });

    auto* zeroPercentLineGraphLabeled = new LineGraphLabeled({{Debug0Percent, 100, 0, colorRanges}}, nbDataPoints,
                                                             {"Debug 0% : ", Debug0Percent, "%"}, colorRanges, 1);
    layout->addWidget(zeroPercentLineGraphLabeled);

    auto* onePercentLineGraphLabeled = new LineGraphLabeled({{Debug1Percent, 100, 0, colorRanges}}, nbDataPoints,
                                                            {"Debug 1% : ", Debug1Percent, "%"}, colorRanges, 1);
    layout->addWidget(onePercentLineGraphLabeled);

    auto* tenPercentLineGraphLabeled = new LineGraphLabeled({{Debug10Percent, 100, 0, colorRanges}}, nbDataPoints,
                                                            {"Debug 10% : ", Debug10Percent, "%"}, colorRanges, 1);
    layout->addWidget(tenPercentLineGraphLabeled);

    auto* fiftyPercentLineGraphLabeled = new LineGraphLabeled({{Debug50Percent, 100, 0, colorRanges}}, nbDataPoints,
                                                              {"Debug 50% : ", Debug50Percent, "%"}, colorRanges, 1);
    layout->addWidget(fiftyPercentLineGraphLabeled);

    auto* oneHundredPercentLineGraphLabeled = new LineGraphLabeled({{Debug100Percent, 100, 0, colorRanges}},
                                                                   nbDataPoints,
                                                                   {"Debug 100% : ", Debug100Percent, "%"}, colorRanges,
                                                                   1);
    layout->addWidget(oneHundredPercentLineGraphLabeled);

    setLayout(layout);
}
}
