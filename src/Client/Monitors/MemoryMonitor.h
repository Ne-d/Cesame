#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <fstream>
#include <string>

namespace Cesame {
class MemoryMonitor {
private:
    // File streams
    const std::string infoFile = "/proc/meminfo";
    std::ifstream infoStream;

    // Helper methods
    static std::string keepNumbers(const std::string& source);

    // Returns a value in kB.
    double getMeminfoLine(unsigned int lineNb);

public:
    MemoryMonitor();

    double total();
    double free();
    double available();
    double used();

private:
    static constexpr int kiB_to_GiB = 1048576;
};
}

#endif //MEMORYMONITOR_H
