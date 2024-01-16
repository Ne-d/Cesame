#ifndef MONITORTYPES_H
#define MONITORTYPES_H

#include <stdexcept>

namespace Cesame {

enum MetricEnum
{
    // CPU Values:
    CPUUsageAverage = 1000,
    CPUUsageCore,
    CPUTemperaturePackage,
    CPUTemperatureCore,
    CPUPowerPackage,
    CPUPowerCore,
    CPUClockAverage,
    CPUClockCore,
    CPUCoreCount,

    // GPU Values:
    GPUUsage = 2000,
    GPUTemperature,
    GPUPower,
    GPUClock,
    VRAMTotal,
    VRAMUsed,
    VRAMFree,

    // Memory values:
    RAMTotal = 3000,
    RAMUsed,
    RAMFree
};

enum MetricsUnit
{
    None,

    // L + Ratio
    Ratio,
    Percent,

    // Size:
    Bit,
    Kilobit,
    Megabit,
    Gigabit,
    Terabit,
    Byte,
    Kilobyte,
    Megabyte,
    Gigabyte,
    Terabyte,

    // Temperature:
    Celsius,
    //Fahrenheit,

    // Power:
    Watt,
    Milliwatt,

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

}

#endif // MONITORTYPES_H
