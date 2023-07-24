#ifndef COLOR_H
#define COLOR_H


#include <QColor>
#include <QList>

#define CESAME_COLOR_WHITE QColor(255, 255, 255, 255)
#define CESAME_COLOR_ORANGE QColor(255, 200, 120, 255)
#define CESAME_COLOR_RED QColor(255, 105, 105, 255)
#define CESAME_COLOR_GREEN QColor(120, 255, 120, 255)

#define CESAME_COLOR_DEFAULT CESAME_COLOR_WHITE
#define CESAME_COLOR_ALARM CESAME_COLOR_ORANGE
#define CESAME_COLOR_CRITICAL CESAME_COLOR_RED

namespace Cesame
{

class ColorRange
{
public:
    ColorRange(double inMin, double inMax, QColor inColor);

    double min;
    double max;
    QColor color;
};


class ColorList : public QList<ColorRange>
{
public:
    QColor interpret(double value);
};

}
#endif // COLOR_H
