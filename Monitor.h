#ifndef MONITOR_H
#define MONITOR_H

#include <variant>

#include <QString>

#include "MonitorTypes.h"

#include "CpuMonitor.h"
#include "GpuMonitor.h"
#include "MemoryMonitor.h"
#include "NetworkMonitor.h"

namespace Cesame
{

typedef std::variant<double, QString, int> MonitorData;

class Monitor
{
public:
    Monitor();
    MonitorData get(MonitorValue value, MonitorUnit unit, int valueIndex, int monitorIndex = 0);
    void update();

private:
    std::vector<CpuMonitor> cpuMonitors;
    std::vector<GpuMonitor> gpuMonitors;
    std::vector<MemoryMonitor> memoryMonitors;
    std::vector<NetworkMonitor> networkMonitors;

};

}

#endif // MONITOR_H
