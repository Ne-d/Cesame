#ifndef CPUMONITOR_H
#define CPUMONITOR_H

#include <chrono>
#include <fstream>

namespace Cesame {
class CpuMonitor {
public:
    CpuMonitor();

public: // Metric getters
    double usageRateAverage();
    double usageRatePerCore(unsigned int core);

    double temperatureAverage();
    double temperaturePackage();
    double temperaturePerCore(unsigned int core);

    double powerDrawPerCore(unsigned int core);
    double powerDrawSumOfCores();
    double powerDrawAverage();
    double powerDrawPackage();

    double clockSpeedPerCore(unsigned int core);
    double clockSpeedAverage();

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
    std::vector<int> totalTime;
    std::vector<int> prevTotalTime;

    std::vector<int> activeTime;
    std::vector<int> prevActiveTime;

    unsigned int coreCount;
};
}

#endif //CPUMONITOR_H
