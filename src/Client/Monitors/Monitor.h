#ifndef MONITOR_H
#define MONITOR_H

#include <fstream>

#include "CpuMonitor.h"
#include "Metric.h"
#include "MetricType.h"
#include "Exceptions.h"

namespace Cesame {
class Monitor {
public: // Methods
    static Metric getMetric(const MetricType& type) {
        switch (type.getName()) {
            case CpuUsageRateAverage:
                return cpuMonitors.at(type.getMonitorIndex()).usageRateAverage();
            case CpuTemperaturePackage:
                return cpuMonitors.at(type.getMonitorIndex()).temperaturePackage();
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
};
}

#endif //MONITOR_H
