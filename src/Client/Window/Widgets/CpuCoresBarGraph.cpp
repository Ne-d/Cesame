#include "CpuCoresBarGraph.h"

#include "Metric.h"
#include "Monitor.h"

namespace Cesame {
CpuCoresBarGraph::CpuCoresBarGraph() {
    const Metric coreCountMetric = Monitor::getMetric(MetricType(CpuCoreCount));
    const int coreCount = std::get<int>(coreCountMetric);

    for (int i = 0; i < coreCount; i++) {
        bars.push_back(new Bar(this, MetricType(CpuUsageRatePerCore, i + 1), 100));
        layout.addWidget(bars.at(i), i / 8, i % 8);
    }

    // TODO: Use proper styling.
    layout.setSpacing(25);
    setLayout(&layout);
}
}
