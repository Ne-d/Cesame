#ifndef MONITORTYPES_H
#define MONITORTYPES_H

#include <stdexcept>

enum MonitorValue
{
    // CPU Values:
    CpuUsageAverage = 1000,
    CpuUsageCore,
    CpuTemperaturePackage,
    CpuTemperatureCore,
    CpuPowerPackage,
    CpuPowerCore,
    CpuClockAverage,
    CpuClockCore,

    // GPU Values:
    GpuUsage = 2000,
    GpuTemperature,
    GpuPower,
    GpuClock,
    VramTotal,
    VramUsed,
    VramFree,

    // Memory values:
    RamTotal = 3000,
    RamUsed,
    RamFree,

    // Network values:
    Ping = 4000
};

enum MonitorUnit
{
    // L + Ratio
    None,
    Percent,

    // Size:
    Bit,
    Kilobit,
    Megabit,
    Gigabit,
    Terrabit,
    Byte,
    Kilobyte,
    Megabyte,
    Gigabyte,
    Terrabyte,

    // Temperature:
    Celsius,
    Fahrenheit,

    // Power:
    Watt,

    // Frequency:
    Hertz,
    Kilohertz,
    Megahertz,
    Gigahertz,

    // Time:
    Nanosecond,
    Microsecond,
    Millisecond,
    Second,
    Minute,
    Hour,
    Day
};

class IncorrectUnitException : public std::exception
{
    const char* what() const noexcept { return "The requested value does not support the chosen unit (e.g. a temperature in gigabytes)"; };
};

#endif // MONITORTYPES_H
