#include "memorymonitor.h"
#include <iostream>

memoryMonitor::memoryMonitor()
{
    // Initialize file streams
    infoStream.open(infoFile);
    if(!infoStream.is_open()) {
        std::cerr << "ERROR in memoryMonitor::memoryMonitor(): could not open /proc/meminfo." << std::endl;
    }
}


void memoryMonitor::update() {
    std::string line = "";
    infoStream.seekg(0);

    // Get Total Memory information
    getline(infoStream, line);
    line = trimLine(line);
    totalMemory = stoi(line);

    // Get Free Memory information
    getline(infoStream, line);
    line = trimLine(line);
    freeMemory = stoi(line);

    // Get Available Memory information
    getline(infoStream, line);
    line = trimLine(line);
    availableMemory = stoi(line);

    // Calculate values in GB.
    totalMemoryGb = (double)totalMemory / divisionFactor;
    freeMemoryGb = (double)freeMemory / divisionFactor;
    usedMemoryGb = (double)(totalMemory - availableMemory) / divisionFactor;
    availableMemoryGb = (double)availableMemory / divisionFactor;
}

// Absolute hellscape of a function to only keep the numbers in a line from /proc/meminfo
std::string memoryMonitor::trimLine(std::string line)
{
    // Removing the last three characters.
    for(int i = 0; i < 3; i++) {
        line.pop_back();
    }

    // IDK how to regex go brrrrrrrrrr
    while(line.front() != '0' && line.front() != '1' && line.front() != '2' && line.front() != '3' && line.front() != '4' &&
          line.front() != '5' && line.front() != '6' && line.front() != '7' && line.front() != '8' && line.front() != '9') {
        line.erase(0, 1);
    }
    // Please kill me.

    return line;
}
