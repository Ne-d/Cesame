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
    int utilization();
    int memoryUtilization();

    // Thermal
    int temperature();
    // Fan speed stuff goes here, can't test it yet.

    // Power draw
    double power();
    double powerEnforcedLimit();

    // Clock speeds
    int getClock(nvmlClockType_t type, nvmlClockId_t id);
    int graphicsClockCurrent();
    int graphicsClockMax();
    int memoryClockCurrent();
    int memoryClockMax();
    // Clock Event Reasons stuff goes here.

    // Memory (VRAM)
    int memoryTotal();
    int memoryUsed();
    int memoryFree();
    int memoryBusWidth();

    // Encoder and decoder
    int encoderUtilization();
    int decoderUtilization();

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
