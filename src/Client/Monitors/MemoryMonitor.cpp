#include "MemoryMonitor.h"

#include <iostream>

#include "Monitor.h"

using namespace Cesame;
using namespace au;

std::string MemoryMonitor::keepNumbers(const std::string& source) {
    std::string target;
    for (const char c : source) {
        if (std::isdigit(c))
            target += c;
    }

    return target;
}

Quantity<Kibi<Bytes>, double> MemoryMonitor::getMeminfoLine(const unsigned int lineNb) {
    std::string line;

    Monitor::goToLine(infoStream, lineNb);
    getline(infoStream, line);
    const std::string numberLine = keepNumbers(line);

    return kibi(bytes)(std::stoi(numberLine));
}

MemoryMonitor::MemoryMonitor() {
    // Initialize file streams
    infoStream.open(infoFile);
    if (!infoStream.is_open())
        throw FileOpenException();
}

Quantity<Gibi<Bytes>, double> MemoryMonitor::total() {
    return getMeminfoLine(0).as(gibi(bytes));
}

Quantity<Gibi<Bytes>, double> MemoryMonitor::free() {
    return getMeminfoLine(1).as(gibi(bytes));
}

Quantity<Gibi<Bytes>, double> MemoryMonitor::available() {
    return getMeminfoLine(2).as(gibi(bytes));
}

Quantity<Gibi<Bytes>, double> MemoryMonitor::used() {
    const Quantity<Giga<Bytes>, double> memoryUsed = total() - available();
    return memoryUsed.as(gibi(bytes));
}
