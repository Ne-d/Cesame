#ifndef CPUMONIT_H
#define CPUMONIT_H

#include <fstream>
#include <vector>
#include <chrono>

#define AMD_MSR_PWR_UNIT 0xC0010299
#define AMD_MSR_CORE_ENERGY 0xC001029A
#define AMD_MSR_PACKAGE_ENERGY 0xC001029B

#define AMD_TIME_UNIT_MASK 0xF0000
#define AMD_ENERGY_UNIT_MASK 0x1F00
#define AMD_POWER_UNIT_MASK 0xF
#define STRING_BUFFER 1024

namespace Cesame
{

class CpuMonitor {
private:
    std::chrono::time_point<std::chrono::steady_clock> currentTimePoint;
    std::chrono::duration<double> deltaTime;

    // File streams
    std::string statFile = "/proc/stat";
    std::string infoFile = "/proc/cpuinfo";
    std::string tempFile = "/sys/class/hwmon/hwmon4/temp1_input"; // TODO: determine automatically / user input

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

private: // MSR / RAPL
    const unsigned int MAX_CPUS = 1024;
    const unsigned int MAX_PACKAGES = 16;
    int totalCores = 0;
    int totalPackages = 0;
    std::vector<int> packageMap;

    void detectPackages();

private:
    void printFields(); // For debug purposes.

public:
    CpuMonitor();
    void update();
    unsigned int coreCount;

    std::vector<double> usagePerCore;
    double temp = 0;
    double power = 0;
    std::vector<double> clockSpeeds;
};

}

#endif // CPUMONIT_H
