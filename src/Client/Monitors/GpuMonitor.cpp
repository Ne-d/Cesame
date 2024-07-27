#include "GpuMonitor.h"

using namespace Cesame;

GpuMonitor::GpuMonitor(const unsigned int deviceIndex) {
    unsigned int deviceCount;

    // If this value isn't overwritten at the end of the constructor, an exception will be thrown.
    device = nullptr;

    nvmlReturn = nvmlInit_v2();
    checkNvmlReturn(NvmlInitException());

    nvmlReturn = nvmlDeviceGetCount_v2(&deviceCount);
    checkNvmlReturn(NvmlDeviceCountException());

    nvmlReturn = nvmlDeviceGetHandleByIndex_v2(deviceIndex, &device);
    checkNvmlReturn(NvmlGetHandleException());
}

int GpuMonitor::utilization() {
    nvmlUtilization_t utilization;
    nvmlReturn = nvmlDeviceGetUtilizationRates(device, &utilization);

    checkNvmlReturn(QueryException());
    return static_cast<int>(utilization.gpu);
}

int GpuMonitor::memoryUtilization() {
    nvmlUtilization_t utilization;
    nvmlReturn = nvmlDeviceGetUtilizationRates(device, &utilization);

    checkNvmlReturn(QueryException());
    return static_cast<int>(utilization.memory);
}

int GpuMonitor::temperature() {
    unsigned int temp;
    nvmlReturn = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

    checkNvmlReturn(QueryException());
    return static_cast<int>(temp);
}

double GpuMonitor::power() {
    unsigned int power;
    nvmlReturn = nvmlDeviceGetPowerUsage(device, &power);

    checkNvmlReturn(QueryException());

    // We divide by 1000 because NVML returns values in williwatts.
    return static_cast<int>(static_cast<double>(power) / 1000);
}

double GpuMonitor::powerEnforcedLimit() {
    unsigned int powerLimit;
    nvmlReturn = nvmlDeviceGetEnforcedPowerLimit(device, &powerLimit);

    checkNvmlReturn(QueryException());
    return static_cast<int>(static_cast<double>(powerLimit) / 1000);
}

int GpuMonitor::graphicsClockCurrent() {
    return getClock(NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT);
}

int GpuMonitor::graphicsClockMax() {
    return getClock(NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CUSTOMER_BOOST_MAX);
}

int GpuMonitor::memoryClockCurrent() {
    return getClock(NVML_CLOCK_MEM, NVML_CLOCK_ID_CURRENT);
}

int GpuMonitor::memoryClockMax() {
    return getClock(NVML_CLOCK_MEM, NVML_CLOCK_ID_CUSTOMER_BOOST_MAX);
}

double GpuMonitor::memoryTotal() {
    nvmlMemory_t memory;
    nvmlReturn = nvmlDeviceGetMemoryInfo(device, &memory);

    checkNvmlReturn(QueryException());
    return static_cast<double>(memory.total) / BYTES_TO_GIBIBYTES;
}

double GpuMonitor::memoryUsed() {
    nvmlMemory_t memory;
    nvmlReturn = nvmlDeviceGetMemoryInfo(device, &memory);

    checkNvmlReturn(QueryException());
    return static_cast<double>(memory.used) / BYTES_TO_GIBIBYTES;
}

double GpuMonitor::memoryFree() {
    nvmlMemory_t memory;
    nvmlReturn = nvmlDeviceGetMemoryInfo(device, &memory);

    checkNvmlReturn(QueryException());
    return static_cast<double>(memory.free) / BYTES_TO_GIBIBYTES;
}

double GpuMonitor::memoryBusWidth() {
    unsigned int busWidth;
    nvmlReturn = nvmlDeviceGetMemoryBusWidth(device, &busWidth);

    checkNvmlReturn(QueryException());
    return static_cast<double>(busWidth) / BYTES_TO_GIBIBYTES;
}


int GpuMonitor::encoderUtilization() {
    unsigned int utilization;
    unsigned int sampling;
    nvmlReturn = nvmlDeviceGetEncoderUtilization(device, &utilization, &sampling);

    checkNvmlReturn(QueryException());
    return static_cast<int>(utilization);
}

int GpuMonitor::decoderUtilization() {
    unsigned int utilization;
    unsigned int sampling;
    nvmlReturn = nvmlDeviceGetDecoderUtilization(device, &utilization, &sampling);

    checkNvmlReturn(QueryException());
    return static_cast<int>(utilization);
}

std::string GpuMonitor::name() {
    constexpr unsigned int length = NVML_DEVICE_NAME_V2_BUFFER_SIZE;
    char name[length];

    nvmlReturn = nvmlDeviceGetName(device, name, length);
    checkNvmlReturn(QueryException());
    return {name};
}

std::string GpuMonitor::pState() {
    nvmlPstates_t pState;
    nvmlReturn = nvmlDeviceGetPerformanceState(device, &pState);

    std::string pStateString(std::to_string(pState));
    return pStateString;
}

int GpuMonitor::getClock(const nvmlClockType_t type, const nvmlClockId_t id) {
    unsigned int clockSpeed;
    nvmlReturn = nvmlDeviceGetClock(device, type, id, &clockSpeed);

    checkNvmlReturn(QueryException());
    return static_cast<int>(clockSpeed);
}

template <typename Exception>
void GpuMonitor::checkNvmlReturn(Exception exception) const {
    if (nvmlReturn != NVML_SUCCESS)
        throw exception;
}
