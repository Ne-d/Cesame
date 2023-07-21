#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <QString>
#include <vector>

#define LINE_WIDTH 2

#define CESAME_FONT_DEFAULT QFont("Mono", 12)

namespace Cesame {

std::string exec(const char* cmd);
QString formatDouble(double n);
double clamp_d(double value, double min, double max);
void printTable(std::vector<double> table);

}

#endif // UTILS_H
