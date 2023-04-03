#ifndef CPUMONITOR_H
#define CPUMONITOR_H

#include <fstream>
#include <vector>

class cpuMonitor {
private:
    // File streams
    std::string statFile = "/proc/stat";
    std::string infoFile = "/proc/cpuinfo";
    std::string tempFile = "/sys/class/hwmon/hwmon4/temp1_input";

    std::ifstream statStream;
    std::ifstream infoStream;
    std::ifstream tempStream;

    // CPU Load
    std::vector<std::vector<int>> fields;

    std::vector<int> totalTime;
    std::vector<int> prevTotalTime;

    std::vector<int> activeTime;
    std::vector<int> prevActiveTime;

    double energy = 0;
    double prevEnergy = 0;

private:
    void printFields(); // For debug purposes.

public:
    cpuMonitor();
    void update();
    unsigned int coreCount;

    std::vector<double> usagePerCore;
    double temp = 0;
    double power = 0;
    std::vector<double> clockSpeeds;
};

#endif // CPUMONITOR_H
