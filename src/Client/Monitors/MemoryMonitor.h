#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <au.hh>
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
    au::Quantity<au::Kibi<au::Bytes>, double> getMeminfoLine(unsigned int lineNb);

public:
    MemoryMonitor();

    au::Quantity<au::Gibi<au::Bytes>, double> total();
    au::Quantity<au::Gibi<au::Bytes>, double> free();
    au::Quantity<au::Gibi<au::Bytes>, double> available();
    au::Quantity<au::Gibi<au::Bytes>, double> used();
};
}

#endif //MEMORYMONITOR_H
