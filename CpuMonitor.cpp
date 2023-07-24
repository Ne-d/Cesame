#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Why the fuck isn't it called 'stringstream'? That wasted 20 minutes of my life.

#include <cmath>
#include <cstdio>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "CpuMonitor.h"
#include "Utils.h"

using namespace Cesame;

CpuMonitor::CpuMonitor() {
    // Initialization of timings
    timePointCurrent = std::chrono::steady_clock::now();

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

    // Preparation of rapl access
    detectPackages();

    coreEnergy.resize(totalCores / 2);
    coreEnergyPrevious.resize(totalCores/ 2);
    packageEnergy.resize(totalPackages);
    packageEnergyPrevious.resize(totalPackages);

    coreEnergyUnits = readMsr(0, AMD_MSR_PWR_UNIT);

    timeUnit = (coreEnergyUnits & AMD_TIME_UNIT_MASK) >> 16;
    energyUnit = (coreEnergyUnits & AMD_ENERGY_UNIT_MASK) >> 8;
    powerUnit = (coreEnergyUnits & AMD_POWER_UNIT_MASK);

    timeUnitAdjusted = pow(0.5, (double)(timeUnit));
    energyUnitAdjusted = pow(0.5, (double)(energyUnit));
    powerUnitAdjusted = pow(0.5, (double)(powerUnit));

    update();
}


void CpuMonitor::update() {
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

    // CPU Power draw section:
    updateEnergy();
    deltaTime = timePointCurrent - timePointPrevious;
    power = (packageEnergy.at(0) - packageEnergyPrevious.at(0)) / deltaTime.count();

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

    for(i = 0; i < MAX_CPUS; i++) // For all cpu cores
    {
        // Set filename to the current cpu core's physical_package_id file.
        sprintf(filename, "/sys/devices/system/cpu/cpu%d/topology/physical_package_id", i);

        // Open the file, to read its content (number) and write it to package.
        fff = fopen(filename, "r");
        if(fff == NULL) break;

        fscanf(fff, "%d", &package);
        fclose(fff);

        if(packageMap.at(package) == -1)
        {
            totalPackages++;
            packageMap.at(package) = i;
        }
    }

    totalCores = i;
}

// TODO: Remove call to exit()
long long CpuMonitor::readMsr(int core, unsigned int reg)
{
    uint64_t data;
    int fd;
    char msrFilename[255];

    sprintf(msrFilename, "/dev/cpu/%d/msr", core);

    fd = open(msrFilename, O_RDONLY);

    if (fd < 0)
    {
        if (errno == ENXIO)
        {
            std::cerr <<"readMsr: No CPU" << core << std::endl;
            exit(2);
        }
        else if (errno == EIO)
        {
            std::cerr << "readMsr: CPU " << core << " doesn't support MSRs" << std::endl;
            exit(3);
        }
        else
        {
            perror("readMsr: open");
            exit(127);
        }
    }

    if (pread(fd, &data, sizeof data, reg) != sizeof data)
    {
        if (errno == EIO)
        {
            std::cerr << "readMsr: CPU " << core << " cannot read MSR " << reg << std::endl;
            exit(4);
        } else {
            perror("readMsr: pread");
            exit(127);
        }
    }

    close(fd);

    return (long long) data;
}

void CpuMonitor::updateEnergy()
{
    timePointPrevious = timePointCurrent;
    timePointCurrent = std::chrono::steady_clock::now();

    for(int i = 0; i < totalCores / 2; i++)
    {
        power = 0;
        coreEnergyPrevious.at(i) = coreEnergy.at(i);
        int coreEnergyRaw = readMsr(i, AMD_MSR_CORE_ENERGY);
        coreEnergy.at(i) = coreEnergyRaw * energyUnitAdjusted;
    }

    for(int i = 0; i <totalPackages; i++)
    {
        packageEnergyPrevious.at(i) = packageEnergy.at(i);
        int packageEnergyRaw = readMsr(i, AMD_MSR_PACKAGE_ENERGY);
        packageEnergy.at(i) = packageEnergyRaw * energyUnitAdjusted;
    }
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
