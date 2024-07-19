
#ifndef CPUMONITOR_H
#define CPUMONITOR_H

#include <fstream>

#include "Monitor.h"

namespace Cesame {
class CpuMonitor {
public:
    CpuMonitor();

public: // Metric getters
    au::Quantity<au::Percent, double> usageRateAverage();
    au::Quantity<au::Percent, double> usageRatePerCore(unsigned int core);

    au::Quantity<au::Celsius, double> temperatureAverage();
    au::QuantityPoint<au::Celsius, double> temperaturePackage();
    au::Quantity<au::Celsius, double> temperaturePerCore(unsigned int core);

    au::Quantity<au::Watts, double> powerDrawPerCore(unsigned int core);
    au::Quantity<au::Watts, double> powerDrawSumOfCores();
    au::Quantity<au::Watts, double> powerDrawAverage();
    au::Quantity<au::Watts, double> powerDrawPackage();

    au::Quantity<au::Mega<au::Hertz>, double> clockSpeedPerCore(unsigned int core);
    au::Quantity<au::Mega<au::Hertz>, double> clockSpeedAverage();

private: // Helper methods
    /**
     * Reads one line of the CPU stats file.
     *
     * @param lineNb The number of the line to read, starting at 0.
     * @return A vector containing each field of the line.
     */
    std::vector<int> getStatLine(unsigned int lineNb);

    double getUsageRateLine(unsigned int lineNb);

private: // Data / state
    // Timings
    std::chrono::time_point<std::chrono::steady_clock> currentTimePoint;
    std::chrono::time_point<std::chrono::steady_clock> previousTimePoint;

    // File streams
    const std::string statFile = "/proc/stat";
    const std::string infoFile = "/proc/cpuinfo";
    const std::string tempFile =
        "/sys/class/hwmon/hwmon4/temp1_input"; // TODO: Determine automatically / through user input.

    std::ifstream statStream;
    std::ifstream infoStream;
    std::ifstream tempStream;

    const unsigned int fieldsPerLine = 10;

    // Raw Data from /proc/stat
    std::vector<std::vector<int>> fields;

    std::vector<int> totalTime;
    std::vector<int> prevTotalTime;

    std::vector<int> activeTime;
    std::vector<int> prevActiveTime;

    unsigned int coreCount;
};

class FileOpenException final : public std::exception {};
}

#endif //CPUMONITOR_H
