
#ifndef METRICTYPE_H
#define METRICTYPE_H

namespace Cesame {
enum MetricName {
    // CPU:
    CpuCoreCount,

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
    FramerateLow,

    // Debugging
    Debug0Percent,
    Debug1Percent,
    Debug10Percent,
    Debug50Percent,
    Debug100Percent
};

class MetricType {
private:
    MetricName name;
    unsigned int index;
    unsigned int monitorIndex;

public:
    // ReSharper disable once CppNonExplicitConvertingConstructor
    MetricType(MetricName name, unsigned int coreIndex = 0, // NOLINT(*-explicit-constructor)
               unsigned int monitorIndex = 0);

    [[nodiscard]] MetricName getName() const;
    [[nodiscard]] unsigned int getIndex() const;
    [[nodiscard]] unsigned int getMonitorIndex() const;

    void setName(const MetricName& name);
    void setIndex(const unsigned int& index);
    void setMonitorIndex(const unsigned int& monitorIndex);
};
}

#endif //METRICTYPE_H
