#ifndef CPUMONIT_H
#define CPUMONIT_H

#include <fstream>
#include <vector>
#include <chrono>

#include "MonitorTypes.h"

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

public: // Methods
    CpuMonitor();

    void update();

    double getUsageAverage(MonitorUnit unit);
    double getUsageCore(MonitorUnit unit, int core);
    double getTemperaturePackage(MonitorUnit unit);
    double getTemperatureCore(MonitorUnit unit, int core);
    double getPowerPackage(MonitorUnit unit);
    double getPowerCore(MonitorUnit unit, int core);
    double getClockAverage(MonitorUnit unit);
    double getClockCore(MonitorUnit unit, int core);


private: // Variables to store monitoring data
    unsigned int coreCount;

    std::vector<double> usagePerCore;
    double temp = 0;
    double power = 0;
    std::vector<double> clockSpeeds;


private:
    std::chrono::time_point<std::chrono::steady_clock> timePointCurrent;
    std::chrono::time_point<std::chrono::steady_clock> timePointPrevious;
    std::chrono::duration<double> deltaTime;

    // File streams
    std::string statFile = "/proc/stat";
    std::string infoFile = "/proc/cpuinfo";
    std::string tempFile = "/sys/class/hwmon/hwmon4/temp1_input"; // TODO: determine automatically / user input

    std::ifstream statStream;
    std::ifstream infoStream;
    std::ifstream tempStream;

    // Raw Data from /proc/stat
    std::vector<std::vector<int>> fields;

    std::vector<int> totalTime;
    std::vector<int> prevTotalTime;

    std::vector<int> activeTime;
    std::vector<int> prevActiveTime;

    // Power Draw
    double energy = 0;
    double prevEnergy = 0;

private: // MSR / RAPL
    const unsigned int MAX_CPUS = 1024;
    const unsigned int MAX_PACKAGES = 16;
    int totalCores = 0;
    int totalPackages = 0;
    std::vector<int> packageMap;
    int coreEnergyUnits;

    unsigned int timeUnit;
    unsigned int energyUnit;
    unsigned int powerUnit;
    double timeUnitAdjusted;
    double energyUnitAdjusted;
    double powerUnitAdjusted;

    std::vector<double> coreEnergy;
    std::vector<double> coreEnergyPrevious;

    std::vector<double> packageEnergy;
    std::vector<double> packageEnergyPrevious;

    void detectPackages();
    long long readMsr(int core, unsigned int reg);
    void updateEnergy();

private:
    void printFields(); // For debug purposes.
};

}

#endif // CPUMONIT_H
