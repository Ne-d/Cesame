#ifndef GPUMONITOR_H
#define GPUMONITOR_H

#include <string>
#include <nvml.h>

namespace Cesame
{

class GpuMonitor
{
private:
    // NVML objects
    nvmlDevice_t device;

    double VRAMDivisionFactor = 1024*1024*128;

public:
    GpuMonitor(int deviceIndex);

    void update();

    // Main queries
    double getUsage();
    double getTemperature();
    double getPower();
    double getClockSpeed(nvmlClockType_t clockType);

    double getVRAMUsage();

    // Additionnal queries (if I spend the time to implement them) (holy shit that's a lot of functions)
    nvmlComputeMode_t getComputeMode();
    nvmlProcessInfo_t getComputeProcesses();
    nvmlProcessInfo_t getGraphicsProcesses();
    unsigned int getPCIeGen();
    unsigned int getPCIeWidth();
    unsigned int getPcieThroughput();
    unsigned int getMaxPCIeGen();
    unsigned int getMaxPCIeWidth();
    unsigned int getMaxPcieSpeed();
    unsigned long long getThrottleReason();
    double getEncoderUsage();
    double getEncoderCapacity();
    void getEncoderStats(); // Still need to define a struct for the return type, void is a placeholder
    double getDecoderUsage();
    double getDriverModel();
    double getEnforcedPowerLimit();
    double getFanSpeed();
    double getMaxClockSpeed();
    double getMaxBoostClockSpeed();
    double getMemoryBusWidth();
    std::string getName();
    int getNumberFans();
    int getNumberCores();
    nvmlPstates_t getPerformanceState();
    double getPowerLimit();
    double getTemperatureThreshold();
    double getTotalEnergyConsumption();
    double getViolationStatus();

public:
    double usage = -1;
    double temperature = -1;
    double power = -1;
    double clockSpeed = -1;

    double totalVRAM = -1;
    double usedVRAM = -1;
    double freeVRAM = -1;
};

}

#endif // GPUMONITOR_H
