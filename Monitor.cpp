#include "Monitor.h"

using namespace Cesame;

Monitor::Monitor()
{
    cpuMonitors.emplace_back();
    gpuMonitors.emplace_back(0);
    memoryMonitors.emplace_back();
    networkMonitors.emplace_back();
}

MonitorData Monitor::get(MonitorValue value, MonitorUnit unit, int valueIndex, int monitorIndex)
{
    switch(value)
    {
        // CPU Values:
    case CpuUsageAverage:
        return cpuMonitors.at(monitorIndex).getUsageAverage(unit);
    case CpuUsageCore:
        return cpuMonitors.at(monitorIndex).getUsageCore(unit, valueIndex);
    case CpuTemperaturePackage:
        return cpuMonitors.at(monitorIndex).getTemperaturePackage(unit);
    case CpuTemperatureCore:
        return cpuMonitors.at(monitorIndex).getTemperatureCore(unit, valueIndex);
    case CpuPowerPackage:
        return cpuMonitors.at(monitorIndex).getPowerPackage(unit);
    case CpuPowerCore:
        return cpuMonitors.at(monitorIndex).getPowerCore(unit, valueIndex);
    case CpuClockAverage:
        return cpuMonitors.at(monitorIndex).getClockAverage(unit);
    case CpuClockCore:
        return cpuMonitors.at(monitorIndex).getClockCore(unit, valueIndex);

        // GPU Values:
    case GpuUsage:
        return gpuMonitors.at(monitorIndex).getUsage(unit);
    case GpuTemperature:
        return gpuMonitors.at(monitorIndex).getTemperature(unit);
    case GpuPower:
        return gpuMonitors.at(monitorIndex).getPower(unit);
    case GpuClock:
        return gpuMonitors.at(monitorIndex).getClock(unit);
    case VramTotal:
        return gpuMonitors.at(monitorIndex).getVramTotal(unit);
    case VramUsed:
        return gpuMonitors.at(monitorIndex).getVramUsed(unit);
    case VramFree:
        return gpuMonitors.at(monitorIndex).getVramFree(unit);

        // Memory Values:
    case RamTotal:
        return memoryMonitors.at(monitorIndex).getTotal(unit);
    case RamUsed:
        return memoryMonitors.at(monitorIndex).getUsed(unit);
    case RamFree:
        return memoryMonitors.at(monitorIndex).getFree(unit);

        // Network Values:
    case Ping:
        return networkMonitors.at(monitorIndex).getPing();
    }
}

void Monitor::update()
{
    for(auto& i : cpuMonitors) { i.update(); }
    for(auto& i : gpuMonitors) { i.update(); }
    for(auto& i : memoryMonitors) { i.update(); }
    for(auto& i : networkMonitors) { i.update(); }
}
