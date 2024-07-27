#include "CpuMonitor.h"

#include <chrono>
#include <iostream>

#include "Monitor.h"

using namespace Cesame;
using namespace std::chrono;

CpuMonitor::CpuMonitor() {
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

    coreCount = 16; // TODO: Determine automatically.

    // Initialize timings
    for (unsigned int i = 0; i <= coreCount; i++) {
        previousTimePoints.push_back(getCurrentTimePoint());
    }

    // Preparation of data arrays
    totalTime.resize(coreCount + 1);
    prevTotalTime.resize(coreCount + 1);
    activeTime.resize(coreCount + 1);
    prevActiveTime.resize(coreCount + 1);
}

double CpuMonitor::usageRateAverage() {
    return getUsageRateLine(0);
}

double CpuMonitor::usageRatePerCore(const unsigned int core) {
    if (core < 1)
        throw std::out_of_range("CpuMonitor::usageRatePerCore : core number must be at least 1.");
    if (core > coreCount)
        throw std::out_of_range("CpuMonitor::usageRatePerCore : core number must be no more than the core count.");

    return getUsageRateLine(core);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::temperatureAverage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

double CpuMonitor::temperaturePackage() {
    // Seek to the beginning of the the temperature file.
    tempStream.seekg(0, std::ifstream::beg);

    // Get the first (and only) line of the file.
    std::string tempBuffer;
    getline(tempStream, tempBuffer);

    // Convert to a double and divide by 1000 because the values are written in thousandths of degrees celsius.
    return std::stod(tempBuffer) / 1000;
}

#pragma region FuturePowerDrawMethods
// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::temperaturePerCore(unsigned int core) { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::powerDrawPerCore(unsigned int core) { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::powerDrawSumOfCores() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::powerDrawAverage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
double CpuMonitor::powerDrawPackage() { // NOLINT(*-convert-member-functions-to-static)
    throw NotImplementedException();
}
#pragma endregion

double CpuMonitor::clockSpeedPerCore(const unsigned int core) {
    std::string line;
    int lineNb = 0;

    std::string clockString;

    // Reset the file stream.
    infoStream.clear();
    infoStream.seekg(0, std::ifstream::beg);

    // For each line of the info file.
    while (getline(infoStream, line)) {
        // If the line contains the clock speed of a core.
        if (line.find("cpu MHz") != std::string::npos) {
            // Remove the first few characters that come before the data.
            // HACK: Magic number.
            line.erase(0, 11);
            lineNb++;

            // If the current line is the one that represents the core we are looking for.
            if (lineNb == core) {
                const auto clockSpeed = std::stod(line);
                return clockSpeed;
            }
        }
    }

    // If we exit the loop (reach the end of the file) without having found a value, yeet an exception.
    throw ValueNotFoundException();
}

double CpuMonitor::clockSpeedAverage() {
    // Yes, the complexity is horrible but I don't give a shit.
    // If it ain't broke, don't fix it.
    // Laugh at perfection. It's boring and keeps you from being done.
    // Premature optimization is the root of all evil.

    double sum = 0;

    for (unsigned int i = 0; i < coreCount; ++i) {
        sum += clockSpeedPerCore(i + 1);
    }

    return sum / coreCount;
}

std::vector<int> CpuMonitor::getStatLine(const unsigned int lineNb) {
    std::string line;
    std::stringstream iss;
    std::string field;

    Monitor::goToLine(statStream, lineNb);

    // Store the contents of the line into the stringstream.
    int fieldNb = 0;
    getline(statStream, line);
    iss.clear();
    iss.str(line);

    std::vector<int> lineFields(FIELDS_PER_LINE);

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
    // If the last update was less than epsilon milliseconds ago
    if (getCurrentTimePoint() - previousTimePoints.at(lineNb) > epsilon) {
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

        previousTimePoints.at(lineNb) = getCurrentTimePoint();
    }

    // TODO: Make this one / two liner more clear cause I'm too lazy to do it now.
    return (static_cast<double>(activeTime.at(lineNb)) - static_cast<double>(prevActiveTime.at(lineNb))) /
        (static_cast<double>(totalTime.at(lineNb)) - static_cast<double>(prevTotalTime.at(lineNb))) * 100;
}

time_point<steady_clock> CpuMonitor::getCurrentTimePoint() {
    return steady_clock::now();
}

