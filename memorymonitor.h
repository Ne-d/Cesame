#ifndef MEMORYMONITOR_H
#define MEMORYMONITOR_H

#include <fstream>

class memoryMonitor
{
private:
    // File streams
    std::ifstream infoStream;
    std::string infoFile = "/proc/meminfo";

    // Monitoring variables (in kB)
    int totalMemory;
    int freeMemory;
    int availableMemory;

    const double divisionFactor = 1000.0 * 1000.0;

public:
    memoryMonitor();

    void update();
    std::string trimLine(std::string line);

public:
    double totalMemoryGb = -1;
    double freeMemoryGb = -1;
    double usedMemoryGb = -1;
    double availableMemoryGb = -1;
};

#endif // MEMORYMONITOR_H
