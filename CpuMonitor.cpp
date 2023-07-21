#include <iostream>
#include <cstdio>
#include <string>
#include <sstream> // Why the fuck isn't it called 'stringstream'? That wasted 20 minutes of my life.

#include "CpuMonitor.h"
#include "Utils.h"

using namespace Cesame;

CpuMonitor::CpuMonitor() {
    // Initialization of timings
    currentTimePoint = std::chrono::steady_clock::now();

    // Initialization of file streams
    statStream.open(statFile);
    if(!statStream.is_open()) {
        std::cerr << "ERROR in cpuMonitor::cpuMonitor(): could not open /proc/stat." << std::endl;
    }

    tempStream.open(tempFile);
    if(!tempStream.is_open()) {
        std::cerr << "ERROR in cpuMonitor::cpuMonitor(): could not open temperature file." << std::endl;
    }

    infoStream.open(infoFile);
    if(!infoStream.is_open()) {
        std::cerr << "ERROR in cpuMonitor::cpuMonitor(): could not open /proc/cpuinfo." << std::endl;
    }

    std::string line;
    // Preparation of data vectors (arrays).
    coreCount = 16; // TODO: Read the "siblings" value from infoFile to adapt to any CPU

    fields.resize(coreCount + 1);
    totalTime.resize(coreCount + 1, 0);
    prevTotalTime.resize(coreCount + 1, 0);
    activeTime.resize(coreCount + 1, 0);
    prevActiveTime.resize(coreCount + 1, 0);

    usagePerCore.resize(coreCount + 1, 0);
    clockSpeeds.resize(coreCount + 1, 0);

    for(unsigned int i = 0; i <= coreCount; i++) {
        fields.at(i).resize(10, 0);
    }

    detectPackages();

    update();
    update(); // I thought one would be enough. I guess not. Stupid program.
    // TODO: Find out what I did wrong here to require two update.
}


void CpuMonitor::update() {
    // Timings
    auto oldTimePoint = currentTimePoint;
    currentTimePoint = std::chrono::steady_clock::now();
    deltaTime = currentTimePoint - oldTimePoint;

    std::string line;
    std::stringstream iss;

    // CPU load section:
    std::string field;
    statStream.seekg(0, statStream.beg); // Seek to the begining of the file

    for(unsigned int l = 0; l <= coreCount; l++) { // Begin looping through all CPU lines
        int fieldNb = 0;
        getline(statStream, line);
        iss.clear();
        iss.str(line);

        while(getline(iss, field, ' ')) { // Begin looping through all fields in the current line

            if(field == "" || field.at(0) == 'c') { continue; } // Ignore the first token indicating cpu number (cpu0, cpu1, cpu2, etc.)

            fields.at(l).at(fieldNb) = stoi(field);
            fieldNb++;
        }
        iss.str(std::string());
    }

    prevTotalTime = totalTime;
    prevActiveTime = activeTime;

    // Reset values of totalTime and activeTime to allow for the next loop to increment them
    for(unsigned int i = 0; i <= coreCount; i++) {
        totalTime.at(i) = 0;
        activeTime.at(i) = 0;
    }

    for(unsigned int l = 0; l <= coreCount; l++) { // Loop to calculate totalTime and activeTime
        for(unsigned int f = 0; f <= 9; f++) {
            totalTime.at(l) += fields.at(l).at(f);

            if(f != 3 && f != 4) { // Add the values to activeTime only if they are not idle or iowait (fields 3 and 4)
                activeTime.at(l) += fields.at(l).at(f);
            }
        }
    }

    // CPU Temperature section:
    tempStream.seekg(0, tempStream.beg);
    std::string tempBuffer;
    getline(tempStream, tempBuffer);
    temp = std::stod(tempBuffer) / 1000;

    // CPU Power section:
    prevEnergy = energy;
    energy = std::stod(exec("sudo rdmsr -d -f 31:0 3221291675")); // TODO: Implement this natively instead of calling a command.

    // CPU Clock sction
    int lineNb = 0;
    double currentCoreClockSpeed = 0;
    double totalClockSpeed = 0;
    std::string clockString = "";

    infoStream.clear();
    infoStream.seekg(0, infoStream.beg);

    while(getline(infoStream, line)) {
        if(line.find("cpu MHz") != std::string::npos) {
            line.erase(0, 11);
            currentCoreClockSpeed = stod(line);
            clockSpeeds.at(lineNb + 1) = currentCoreClockSpeed;
            totalClockSpeed += currentCoreClockSpeed;
            lineNb++;
        }
    }

    clockSpeeds.at(0) = totalClockSpeed / (double) coreCount;

    // Updating variables to store all monitoring data

    // CPU Usage
    for(unsigned int i = 0; i <= coreCount; i++) {
        usagePerCore.at(i) = (((double)activeTime.at(i) - (double)prevActiveTime.at(i)) /
                ((double)totalTime.at(i) - (double)prevTotalTime.at(i))) * 100.0;
    }

    // Power draw
    //power = std::abs(energy - prevEnergy) / 65359.47712; // Division factor because the MSR reports energy in 15.3 joule increments.
    power = 0;
}

void CpuMonitor::detectPackages()
{
    char filename[BUFSIZ];
    FILE *fff;
    int package;
    unsigned int i = 0;

    // Initialize all values of packageMap to -1
    for(i = 0; i < MAX_PACKAGES; i++)
    {
        packageMap.push_back(-1);
    }

    // Debug:
    std::cout << "\t";

    for(i = 0; i < MAX_CPUS; i++) // For all cpu cores
    {
        // Set filename to the current cpu core's physical_package_id file.
        sprintf(filename, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id", i);

        // Open the file, to read its content (number) and write it to package.
        fff = fopen(filename, "r");
        if(fff == NULL) break;

        fscanf(fff, "%d", &package);
        // Debug:
        std::cout << i << "(" << package << ")";
        if (i % 8 == 7) std::cout << "\n\t";
        else std::cout << ", ";
        fclose(fff);

        if(packageMap.at(package) == -1)
        {
            totalPackages++;
            packageMap.at(package) = i;
        }
    }

    // Debug:
    std::cout << "\n";

    totalCores = i;

    // Debug:
    std::cout << "\tDetected " << totalCores << " cores in " << totalPackages << " packages\n" << std::endl;
}

// For debugging purposes
void CpuMonitor::printFields()
{
    for(unsigned int l = 0; l <= coreCount; l++) {
        for(int f = 0; f <= 9; f++) {
            std::cout << fields.at(l).at(f) << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}
