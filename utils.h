#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <QString>
#include <vector>

#define COLOR_WHITE QColor(255, 255, 255, 255)
#define COLOR_ORANGE QColor(255, 192, 77, 255)
#define COLOR_RED QColor(255, 77, 77, 255)
#define LINE_WIDTH 2

std::string exec(const char* cmd);
QString formatDouble(double n);
double clamp_d(double value, double min, double max);
void printTable(std::vector<double> table);

#endif // UTILS_H
