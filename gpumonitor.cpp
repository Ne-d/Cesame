#include "gpumonitor.h"

#include <iostream>
#include <nvml.h>


gpuMonitor::gpuMonitor(int deviceIndex) {
    nvmlReturn_t nvmlReturn;
    unsigned int deviceCount;

    nvmlReturn = nvmlInit_v2();
    if(nvmlReturn == NVML_SUCCESS)
    {
        //std::cout << "initNvml: NVML successfully initialized" << std::endl;
        // May need to log this.
    }
    else
    {
        std::cout << "Error: NVML failed to initialize" << std::endl;
    }

    nvmlReturn = nvmlDeviceGetCount_v2(&deviceCount);
    if(nvmlReturn == NVML_SUCCESS)
    {
        //std::cout << "initNvml: Device count: " << deviceCount << std::endl;
        // May need to log this.
    }
    else
    {
        std::cout << "Error: nvmlDeviceGetCount failed with error " << nvmlReturn << std::endl;
    }

    nvmlReturn = nvmlDeviceGetHandleByIndex_v2(deviceIndex, &device); // Device variable is set to chosen device
                                                                      // Based on deviceIndex
    if(nvmlReturn == NVML_SUCCESS)
    {
        //std::cout << "initNvml: Successfully retreived handle for device of index 0." << std::endl;
        // May need to log this.
    }
    else
    {
        std::cout << "Error: nvmlDeviceGetHandlByIndex failed with error " << nvmlReturn << std::endl;
    }
}

void gpuMonitor::update()
{
    nvmlReturn_t nvmlReturn;

    { // Utilization
        nvmlUtilization_t utilization;
        nvmlReturn = nvmlDeviceGetUtilizationRates(device, &utilization);

        if(nvmlReturn == NVML_SUCCESS) {
            usage = utilization.gpu;
        }
    }

    { // Temperature
        unsigned int temp;

        nvmlReturn = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

        if(nvmlReturn == NVML_SUCCESS) {
            temperature = (double)temp;
        }
    }

    { // Power
        unsigned int reportedPower;

        nvmlReturn = nvmlDeviceGetPowerUsage(device, &reportedPower);

        if(nvmlReturn == NVML_SUCCESS) {
            power = (double)reportedPower / 1000.0;
        }
    }

    { // Clock
        nvmlClockId_t clockId = NVML_CLOCK_ID_CURRENT;
        unsigned int reportedClock;

        nvmlReturn = nvmlDeviceGetClock(device, NVML_CLOCK_GRAPHICS, clockId, &reportedClock);

        if(nvmlReturn == NVML_SUCCESS) {
            clockSpeed = (double)reportedClock;
        }

    }

    { // VRAM
        nvmlBAR1Memory_t bar1;

        nvmlReturn = nvmlDeviceGetBAR1MemoryInfo(device, &bar1);

        if(nvmlReturn == NVML_SUCCESS) {
            totalVRAM = (double)bar1.bar1Total / VRAMDivisionFactor;
            usedVRAM = (double)bar1.bar1Used / VRAMDivisionFactor;
            freeVRAM = (double)bar1.bar1Free / VRAMDivisionFactor;
        }
    }
}
