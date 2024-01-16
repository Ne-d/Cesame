#include "MetricsManager.h"
#include "common.h"

#include <iostream>

using namespace Cesame;

// For some reason C++ doesn't actually define static member variables inside of the class.
std::string MetricsManager::shmName;
boost::interprocess::managed_shared_memory* MetricsManager::shm;

void MetricsManager::init() {
    shmName = "CesameServer";
    // TODO: Handle situation where the server is not started.
    try {
        shm = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, shmName.c_str());
    }
    catch(...) { // TODO: Find the precise needed exception
        std::cerr << "MetricsManager: init: could not open shared memory object." << std::endl;
        exit(EXIT_FAILURE);
    }
}


template <typename T>
T MetricsManager::shmGet(std::string name) {
    const T* ptr = shm->find<T>(name.c_str()).first;

    if(ptr == nullptr) {
        throw new ShmNotFoundException();
    }

    return *ptr;
}


double MetricsManager::unitMultiplier(MetricsUnit unit) {
    switch (unit) {
    case None: return 1;

    // L + Ratio
    case Ratio: return 0.01; // Converting from percent to ratio
    case Percent: return 1; // Values are in percent by default

    // Data
    case Bit: return 8;
    case Kilobit: return 8'000;
    case Megabit: return 8'000'000;
    case Gigabit: return 8'000'000'000;
    case Terabit: return 8'000'000'000'000;

    case Byte: return 1; // Values are in bytes by default
    case Kilobyte: return 1'000;
    case Megabyte: return 1'000'000;
    case Gigabyte: return 1'000'000'000;
    case Terabyte: return 1'000'000'000'000;

    // Temperature
    case Celsius: return 1; // Values are in °C by default
    // Farentheit is not suppoerted at the time because it requires an addition and a multiplication

    // Power
    case Watt: return 1; // Values are in Watts by default
    case Milliwatt: return 1'000;

    // Frequency
    case Hertz: return 1'000'000;
    case Kilohertz: return 1'000;
    case Megahertz: return 1; // Values are in MHz by default
    case Gigahertz: return 0.1;

    // Time
    case Nanosecond: return 1'000'000'000;
    case Microsecond: return 1'000'000;
    case Millisecond: return 1'000;
    case Second: return 1; // Values are in seconds by default
    case Minute: return 1/60;
    case Hour: return 1/3600;
    case Day: return 1/86400; // 3600 * 24 = 86400
    }

    throw new IncorrectUnitException(); // If we somehow didn't retun in the switch, throw an exception.
}


Metric MetricsManager::getMetric(MetricEnum name, Cesame::MetricsUnit unit, unsigned int index) {
    switch (name) {

    // CPU
    case CPUUsageAverage:
        return shmGet<double>(CPUUsageAverageKey) * unitMultiplier(unit);

    case CPUUsageCore:
    {
        auto pair = shm->find<std::vector<double>>(CPUUsageCoreKey);
        std::vector<double>* vector = pair.first;
        double rawUsage = vector->at(index);
        double processedUsage =  rawUsage * unitMultiplier(unit);
        return processedUsage;
    }

    case CPUTemperaturePackage:
        return shmGet<double>(CPUTemperaturePackagekey) * unitMultiplier(unit);

    case CPUTemperatureCore:
        return shmGet<std::vector<double>>(CPUTemperaturePerCoreKey).at(index) * unitMultiplier(unit);

    case CPUPowerPackage:
        return shmGet<double>(CPUPowerPackageKey) * unitMultiplier(unit);

    case CPUPowerCore:
        return shmGet<std::vector<double>>(CPUPowerPerCoreKey).at(index) * unitMultiplier(unit);

    case CPUClockAverage:
        return shmGet<double>(CPUClockSpeedAverageKey) * unitMultiplier(unit);

    case CPUClockCore:
        return shmGet<std::vector<double>>(CPUClockSpeedCoreKey).at(index) * unitMultiplier(unit);

    case CPUCoreCount:
        return shmGet<int>(CPUCoreCountKey);

    // GPU
    case GPUUsage:
        return shmGet<double>(GPUUsageKey) * unitMultiplier(unit);

    case GPUTemperature:
        return shmGet<double>(GPUTemperatureKey) * unitMultiplier(unit);

    case GPUPower:
        return shmGet<double>(GPUPowerKey) * unitMultiplier(unit);

    case GPUClock:
        return shmGet<double>(GPUClockSpeedKey) * unitMultiplier(unit);

    case VRAMTotal:
        return shmGet<double>(GPUVRAMTotalKey) * unitMultiplier(unit);

    case VRAMUsed:
        return shmGet<double>(GPUVRAMUsedKey) * unitMultiplier(unit);

    case VRAMFree:
        return shmGet<double>(GPUVRAMFreeKey) * unitMultiplier(unit);

    // Memory
    case RAMTotal:
        return shmGet<double>(MemoryTotalKey) * unitMultiplier(unit);

    case RAMUsed:
        return shmGet<double>(MemoryUsedKey) * unitMultiplier(unit);

    case RAMFree:
        return shmGet<double>(MemoryFreeKey) * unitMultiplier(unit);
    }

    throw new IncorrectMetricException(); // If we somehow didn't return in the switch, throw an exception.
}

MetricDefinition Cesame::mDef(MetricEnum metric, MetricsUnit unit, unsigned int index) {
    MetricDefinition def;

    def.metric = metric;
    def.unit = unit;
    def.index = index;

    return def;
}
