#include "MemoryMonitor.h"

#include <iostream>

#include "Monitor.h"

using namespace Cesame;

std::string MemoryMonitor::keepNumbers(const std::string& source) {
    std::string target;
    for (const char c : source) {
        if (std::isdigit(c))
            target += c;
    }

    return target;
}

double MemoryMonitor::getMeminfoLine(const unsigned int lineNb) {
    std::string line;

    Monitor::goToLine(infoStream, lineNb);
    getline(infoStream, line);
    const std::string numberLine = keepNumbers(line);

    return std::stoi(numberLine);
}

MemoryMonitor::MemoryMonitor() {
    // Initialize file streams
    infoStream.open(infoFile);
    if (!infoStream.is_open())
        throw FileOpenException();
}

double MemoryMonitor::total() {
    return getMeminfoLine(0) / kiB_to_GiB;
}

double MemoryMonitor::free() {
    return getMeminfoLine(1) / kiB_to_GiB;
}

double MemoryMonitor::available() {
    return getMeminfoLine(2) / kiB_to_GiB;
}

double MemoryMonitor::used() {
    const double memoryUsed = total() - available();
    return memoryUsed;
}
