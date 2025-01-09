#ifndef MONITOR_H
#define MONITOR_H

#include <fstream>

#include "Metric.h"
#include "MetricType.h"
#include "CpuMonitor.h"
#include "GpuMonitor.h"
#include "MemoryMonitor.h"
#include "Exceptions.h"

namespace Cesame {
class GpuMonitor;

class Monitor {
public: // Methods
    static Metric getMetric(const MetricType& type) {
        switch (type.getName()) {
            case CpuCoreCount:
                return cpuMonitors.at(type.getMonitorIndex()).coreCount();
            case CpuUsageRateAverage:
                return cpuMonitors.at(type.getMonitorIndex()).usageRateAverage();
            case CpuUsageRatePerCore:
                return cpuMonitors.at(type.getMonitorIndex()).usageRatePerCore(type.getIndex());
            case CpuTemperaturePackage:
                return cpuMonitors.at(type.getMonitorIndex()).temperaturePackage();
            case CpuClockSpeedPerCore:
                return cpuMonitors.at(type.getMonitorIndex()).clockSpeedPerCore(type.getIndex());
            case CpuClockSpeedAverage:
                return cpuMonitors.at(type.getMonitorIndex()).clockSpeedAverage();
            case GpuUsageRate:
                return gpuMonitors.at(type.getMonitorIndex()).utilization();
            case GpuMemoryUsageRate:
                return gpuMonitors.at(type.getMonitorIndex()).memoryUtilization();
            case GpuTemperature:
                return gpuMonitors.at(type.getMonitorIndex()).temperature();
            case GpuPowerUsage:
                return gpuMonitors.at(type.getMonitorIndex()).power();
            case GpuEnforcedPowerLimit:
                return gpuMonitors.at(type.getMonitorIndex()).powerEnforcedLimit();
            case GpuClockGraphicsCurrent:
                return gpuMonitors.at(type.getMonitorIndex()).graphicsClockCurrent();
            case GpuClockGraphicsMax:
                return gpuMonitors.at(type.getMonitorIndex()).graphicsClockMax();
            case GpuClockGraphicsEventReasons:
                throw NotImplementedException();
            case GpuClockMemoryCurrent:
                return gpuMonitors.at(type.getMonitorIndex()).memoryClockCurrent();
            case GpuClockMemoryMax:
                return gpuMonitors.at(type.getMonitorIndex()).memoryClockMax();
            case GpuClockMemoryEventReasons:
                throw NotImplementedException();
            case GpuMemoryTotal:
                return gpuMonitors.at(type.getMonitorIndex()).memoryTotal();
            case GpuMemoryUsed:
                return gpuMonitors.at(type.getMonitorIndex()).memoryUsed();
            case GpuMemoryFree:
                return gpuMonitors.at(type.getMonitorIndex()).memoryFree();
            case GpuMemoryBusWidth:
                return gpuMonitors.at(type.getMonitorIndex()).memoryBusWidth();
            case GpuEncoderUsageRate:
                return gpuMonitors.at(type.getMonitorIndex()).encoderUtilization();
            case GpuDecoderUsageRate:
                return gpuMonitors.at(type.getMonitorIndex()).decoderUtilization();
            case GpuName:
                return gpuMonitors.at(type.getMonitorIndex()).name();
            case GpuPState:
                return gpuMonitors.at(type.getMonitorIndex()).pState();
            case MemoryTotal:
                return memoryMonitors.at(type.getMonitorIndex()).total();
            case MemoryAvailable:
                return memoryMonitors.at(type.getMonitorIndex()).available();
            case MemoryUsed:
                return memoryMonitors.at(type.getMonitorIndex()).used();
            case Debug0Percent:
                return 0.0;
            case Debug1Percent:
                return 1.0;
            case Debug10Percent:
                return 10.0;
            case Debug50Percent:
                return 50.0;
            case Debug100Percent:
                return 100.0;
            default:
                throw NotImplementedException();
        }
    }

    /**
     * Moves the file stream's cursor to the beginning of the desired line.
     *
     * @param stream The stream to set to the desried line.
     * @param lineNb The number of the line to set the stream to, starting at 0.
     */
    static void goToLine(std::ifstream& stream, const unsigned int lineNb) {
        stream.seekg(0, std::ifstream::beg);
        for (int i = 0; i < lineNb; ++i) {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

private: // Data
    inline static std::vector<CpuMonitor> cpuMonitors = [] {
        std::vector<CpuMonitor> cpuMonitors;
        cpuMonitors.emplace_back();
        return cpuMonitors;
    }();

    inline static std::vector<GpuMonitor> gpuMonitors = [] {
        std::vector<GpuMonitor> gpuMonitors;
        gpuMonitors.emplace_back(0);
        return gpuMonitors;
    }();

    inline static std::vector<MemoryMonitor> memoryMonitors = [] {
        std::vector<MemoryMonitor> memoryMonitors;
        memoryMonitors.emplace_back();
        return memoryMonitors;
    }();
};
}

#endif //MONITOR_H
