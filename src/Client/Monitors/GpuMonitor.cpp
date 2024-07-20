#include "GpuMonitor.h"

using namespace Cesame;
using namespace au;

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

Quantity<Percent, unsigned int> GpuMonitor::utilization() {
    nvmlUtilization_t utilization;
    nvmlReturn = nvmlDeviceGetUtilizationRates(device, &utilization);

    checkNvmlReturn(QueryException());
    return percent(utilization.gpu);
}

Quantity<Percent, unsigned int> GpuMonitor::memoryUtilization() {
    nvmlUtilization_t utilization;
    nvmlReturn = nvmlDeviceGetUtilizationRates(device, &utilization);

    checkNvmlReturn(QueryException());
    return percent(utilization.memory);
}

QuantityPoint<Celsius, unsigned int> GpuMonitor::temperature() {
    unsigned int temp;
    nvmlReturn = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temp);

    checkNvmlReturn(QueryException());
    return celsius_pt(temp);
}

Quantity<Watts, double> GpuMonitor::power() {
    unsigned int power;
    nvmlReturn = nvmlDeviceGetPowerUsage(device, &power);

    checkNvmlReturn(QueryException());
    return milli(watts)(static_cast<double>(power)).as(watts);
}

Quantity<Watts, double> GpuMonitor::powerEnforcedLimit() {
    unsigned int powerLimit;
    nvmlReturn = nvmlDeviceGetEnforcedPowerLimit(device, &powerLimit);

    checkNvmlReturn(QueryException());
    return milli(watts)(static_cast<double>(powerLimit)).as(watts);
}

Quantity<Mega<Hertz>, unsigned int> GpuMonitor::graphicsClockCurrent() {
    return getClock(NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CURRENT);
}

Quantity<Mega<Hertz>, unsigned int> GpuMonitor::graphicsClockMax() {
    return getClock(NVML_CLOCK_GRAPHICS, NVML_CLOCK_ID_CUSTOMER_BOOST_MAX);
}

Quantity<Mega<Hertz>, unsigned int> GpuMonitor::memoryClockCurrent() {
    return getClock(NVML_CLOCK_MEM, NVML_CLOCK_ID_CURRENT);
}

Quantity<Mega<Hertz>, unsigned int> GpuMonitor::memoryClockMax() {
    return getClock(NVML_CLOCK_MEM, NVML_CLOCK_ID_CUSTOMER_BOOST_MAX);
}

Quantity<Percent, unsigned int> GpuMonitor::encoderUtilization() {
    unsigned int utilization;
    unsigned int sampling;
    nvmlReturn = nvmlDeviceGetEncoderUtilization(device, &utilization, &sampling);

    checkNvmlReturn(QueryException());
    return percent(utilization);
}

Quantity<Percent, unsigned int> GpuMonitor::decoderUtilization() {
    unsigned int utilization;
    unsigned int sampling;
    nvmlReturn = nvmlDeviceGetDecoderUtilization(device, &utilization, &sampling);

    checkNvmlReturn(QueryException());
    return percent(utilization);
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

Quantity<Mega<Hertz>, unsigned int> GpuMonitor::getClock(const nvmlClockType_t type, const nvmlClockId_t id) {
    unsigned int clockSpeed;
    nvmlReturn = nvmlDeviceGetClock(device, type, id, &clockSpeed);

    checkNvmlReturn(QueryException());
    return mega(hertz)(clockSpeed);
}

template <typename Exception>
void GpuMonitor::checkNvmlReturn(Exception exception) const {
    if (nvmlReturn != NVML_SUCCESS)
        throw exception;
}
