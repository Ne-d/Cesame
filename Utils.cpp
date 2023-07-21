#include "Utils.h"
#include <array>
#include <bits/unique_ptr.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <QString>
#include <iostream>
#include <fmt/core.h>

using namespace Cesame;

std::string Cesame::exec(const char *cmd)
{
    std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
}

QString Cesame::formatDouble(double n)
{
    std::ostringstream str;
    str << std::fixed;
    str << std::setprecision(2);
    str << n;
    return QString(str.str().c_str());
}


double Cesame::clamp_d(double value, double min, double max) {
    if(value < min) {
        return min;
    }
    if(value > max) {
        return max;
    }
    return value;
}

void Cesame::printTable(std::vector<double> table)
{
    for(unsigned int i = 0; i < table.size(); i++)
    {
        std::cout << table.at(i) << " ";
    }

    std::cout << std::endl;
}
