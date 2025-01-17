#ifndef GPUMONITOR_H
#define GPUMONITOR_H

#include <nvml.h>
#include <string>

namespace Cesame {
class GpuMonitor {
private: // Data
    nvmlDevice_t device;
    nvmlReturn_t nvmlReturn;

public: // Methods
    explicit GpuMonitor(unsigned int deviceIndex);

    // Utilization
    double utilization();
    double memoryUtilization();

    // Thermal
    double temperature();
    // Fan speed stuff goes here, can't test it yet.

    // Power draw
    double power();
    double powerEnforcedLimit();

    // Clock speeds
    double getClock(nvmlClockType_t type, nvmlClockId_t id);
    double graphicsClockCurrent();
    double graphicsClockMax();
    double memoryClockCurrent();
    double memoryClockMax();
    // Clock Event Reasons stuff goes here.

    // Memory (VRAM)
    double memoryTotal();
    double memoryUsed();
    double memoryFree();
    double memoryBusWidth();

    // Encoder and decoder
    double encoderUtilization();
    double decoderUtilization();

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

private:
    static constexpr double BYTES_TO_GIBIBYTES = 1073741824;

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
