
#ifndef METRICTYPE_H
#define METRICTYPE_H

namespace Cesame {
enum MetricName {
    // CPU:
    CpuUsageRatePerCore,
    CpuUsageRateAverage,

    CpuTemperaturePerCore,
    CpuTemperatureAverage,
    CpuTemperaturePackage,

    CpuPowerDrawPerCore,
    CpuPowerDrawSumOfCores,
    CpuPowerDrawAverage,
    CpuPowerDrawPackage,

    CpuClockSpeedPerCore,
    CpuClockSpeedAverage,

    // GPU:
    GpuUsageRate,
    GpuMemoryUsageRate,

    GpuTemperature,
    GpuFanSpeed,
    GpuTargetFanSpeed,
    GpuMinFanSpeed,
    GpuMaxFanSpeed,

    GpuPowerUsage,
    GpuEnforcedPowerLimit,

    GpuClockGraphicsCurrent,
    GpuClockGraphicsMax,
    GpuClockGraphicsEventReasons,

    GpuClockMemoryCurrent,
    GpuClockMemoryMax,
    GpuClockMemoryEventReasons,

    GpuMemoryTotal,
    GpuMemoryUsed,
    GpuMemoryFree,
    GpuMemoryBusWidth,

    GpuEncoderUsageRate,
    GpuDecoderUsageRate,

    GpuName,
    GpuBrand,
    GpuArchitecture,
    GpuPState,

    // Memory (RAM)
    MemoryTotal,
    MemoryAvailable,
    MemoryUsed,
    MemoryUsedByCache,
    MemoryUsedIncludingCache,

    // Storage
    StorageAvailable,
    StorageFree,
    StorageUsed,
    StorageTransferRate,
    StorageUsageRate,

    // Frames
    Frametime,
    Framerate,
    FramerateLow
};

class MetricType {
private:
    MetricName name;
    unsigned int coreIndex;
    unsigned int monitorIndex;

public:
    explicit MetricType(MetricName name, unsigned int coreIndex = 0, unsigned int monitorIndex = 0);

    MetricName getName() const;
    unsigned int getCoreIndex() const;
    unsigned int getMonitorIndex() const;

    void setName(const MetricName& name);
    void setCoreIndex(const unsigned int& coreIndex);
    void setMonitorIndex(const unsigned int& monitorIndex);
};
}

#endif //METRICTYPE_H
