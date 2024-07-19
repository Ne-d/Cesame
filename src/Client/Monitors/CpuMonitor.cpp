#include "CpuMonitor.h"

#include <iostream>

using namespace Cesame;
using namespace std::chrono;
using namespace au;

CpuMonitor::CpuMonitor() {
    // Initialize timings
    currentTimePoint = steady_clock::now();

    // Initialize file streams
    statStream.open(statFile);
    if (!statStream.is_open())
        throw FileOpenException();

    tempStream.open(tempFile);
    if (!tempStream.is_open())
        throw FileOpenException();

    infoStream.open(infoFile);
    if (!infoStream.is_open())
        throw FileOpenException();

    // Preparation of data arrays
    coreCount = 16; // TODO: Determine automatically.

    fields.resize(coreCount + 1);
    totalTime.resize(coreCount + 1);
    prevTotalTime.resize(coreCount + 1);
    activeTime.resize(coreCount + 1);
    prevActiveTime.resize(coreCount + 1);

    // Resize all second-dimension vectors representing the fields of the stat file (because there are 10 fields per line).
    for (std::vector<int> vector : fields) {
        vector.resize(10, 0);
    }
}

Quantity<Percent, double> CpuMonitor::usageRateAverage() {
    return percent(getUsageRateLine(0));
}

Quantity<Percent, double> CpuMonitor::usageRatePerCore(const unsigned int core) {
    return percent(getUsageRateLine(core));
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Celsius, double> CpuMonitor::temperatureAverage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

QuantityPoint<Celsius, double> CpuMonitor::temperaturePackage() {
    tempStream.seekg(0, std::ifstream::beg);
    std::string tempBuffer;
    getline(tempStream, tempBuffer);

    return celsius_pt(std::stod(tempBuffer) / 1000);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Celsius, double>
CpuMonitor::temperaturePerCore(unsigned int core) { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Watts, double>
CpuMonitor::powerDrawPerCore(unsigned int core) { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Watts, double> CpuMonitor::powerDrawSumOfCores() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Watts, double> CpuMonitor::powerDrawAverage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
Quantity<Watts, double> CpuMonitor::powerDrawPackage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

au::Quantity<au::Mega<au::Hertz>, double> CpuMonitor::clockSpeedPerCore(unsigned int core) {}

std::vector<int> CpuMonitor::getStatLine(const unsigned int lineNb) {
    std::string line;
    std::stringstream iss;
    std::string field;

    // Go to the desired line.
    statStream.seekg(0, std::ifstream::beg);
    for (int i = 0; i < lineNb; ++i) {
        statStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Store the contents of the line into the stringstream.
    int fieldNb = 0;
    getline(statStream, line);
    iss.clear();
    iss.str(line);

    std::vector<int> lineFields(fieldsPerLine);

    // For every field in the line.
    while (getline(iss, field, ' ')) {
        // Ignore the first token indicating cpu number
        if (field.empty() || field.at(0) == 'c')
            continue;

        lineFields.at(fieldNb) = std::stoi(field);
        fieldNb++;
    }

    return lineFields;
}

double CpuMonitor::getUsageRateLine(const unsigned int lineNb) {
    const std::vector<int> lineFields = getStatLine(lineNb);

    prevTotalTime.at(lineNb) = totalTime.at(lineNb);
    prevActiveTime.at(lineNb) = activeTime.at(lineNb);

    // Reset values of totalTime and activeTime to allow for the next loop to increment them
    totalTime.at(lineNb) = 0;
    activeTime.at(lineNb) = 0;

    for (unsigned int f = 0; f <= 9; f++) { // For every field in the line
        // Accumulate values of the fields into totalTime
        totalTime.at(lineNb) += lineFields.at(f);

        // Accumulate values into activeTime only if they are not idle or iowait (fields 3 and 4)
        if (f != 3 && f != 4)
            activeTime.at(lineNb) += lineFields.at(f);
    }

    // TODO: Make this one / two liner more clear cause I'm too lazy to do it now.
    return ((static_cast<double>(activeTime.at(lineNb)) - static_cast<double>(prevActiveTime.at(lineNb))) /
        (static_cast<double>(totalTime.at(lineNb)) - static_cast<double>(prevTotalTime.at(lineNb)))) * 100;
}

