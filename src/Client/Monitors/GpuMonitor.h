#ifndef GPUMONITOR_H
#define GPUMONITOR_H

#include <au.hh>
#include <nvml.h>

// ReSharper disable once CppInconsistentNaming
namespace au {
using BytesPerSecond = decltype(Bytes{} / Seconds{});
// ReSharper disable once CppInconsistentNaming
// Following the Au code style when defining units, rather than Cesame's own code style.
constexpr auto bytes_per_second = bytes / second;
}

namespace Cesame {
class GpuMonitor {
private: // Data
    nvmlDevice_t device;
    nvmlReturn_t nvmlReturn;

public: // Methods
    explicit GpuMonitor(unsigned int deviceIndex);

    // Utilization
    au::Quantity<au::Percent, unsigned int> utilization();
    au::Quantity<au::Percent, unsigned int> memoryUtilization();

    // Thermal
    au::QuantityPoint<au::Celsius, unsigned int> temperature();
    // Fan speed stuff goes here, can't test it yet.

    // Power draw
    au::Quantity<au::Watts, double> power();
    au::Quantity<au::Watts, double> powerEnforcedLimit();

    // Clock speeds
    au::Quantity<au::Mega<au::Hertz>, unsigned int> getClock(nvmlClockType_t type, nvmlClockId_t id);
    au::Quantity<au::Mega<au::Hertz>, unsigned int> graphicsClockCurrent();
    au::Quantity<au::Mega<au::Hertz>, unsigned int> graphicsClockMax();
    au::Quantity<au::Mega<au::Hertz>, unsigned int> memoryClockCurrent();
    au::Quantity<au::Mega<au::Hertz>, unsigned int> memoryClockMax();
    // Clock Event Reasons stuff goes here.

    // Memory (VRAM)
    au::Quantity<au::Giga<au::Bytes>, unsigned long long> memoryTotal;
    au::Quantity<au::Giga<au::Bytes>, unsigned long long> memoryUsed;
    au::Quantity<au::Giga<au::Bytes>, unsigned long long> memoryFree;
    au::Quantity<au::Giga<au::BytesPerSecond>, unsigned long long> memoryBusWidth;

    // Encoder and decoder
    au::Quantity<au::Percent, unsigned int> encoderUtilization();
    au::Quantity<au::Percent, unsigned int> decoderUtilization();

    // Misc
    std::string name();
    std::string pState();

private: // Helper methods
    /**
     * Checks that the last NVML call was successful.
     * Requires that the return value of said NVML call was assigned to the nvmlReturn field.
     *
     * @tparam Exception The type of exception to throw in case of a failure.
     * @param exception The value of the exception to throw in case of a failure.
     */
    template <typename Exception>
    void checkNvmlReturn(Exception exception) const;

public: // Exceptions
    class NvmlInitException final : public std::exception {
        [[nodiscard]] const char* what() const noexcept override { return "NVML failed to initialize."; }
    };

    class NvmlDeviceCountException final : public std::exception {
        [[nodiscard]] const char* what() const noexcept override { return "NVML failed to get device count."; }
    };

    class NvmlGetHandleException final : public std::exception {
        [[nodiscard]] const char* what() const noexcept override { return "NVML failed to get device handle."; }
    };

    class QueryException final : public std::exception {
        [[nodiscard]] const char* what() const noexcept override { return "NVML failed to query GPU info."; }
    };
};
}

#endif //GPUMONITOR_H
