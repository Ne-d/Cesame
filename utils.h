#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <QString>

std::string exec(const char* cmd);
QString formatDouble(double n);
double clamp_d(double value, double min, double max);

#endif // UTILS_H
