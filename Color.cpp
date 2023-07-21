#include "Color.h"

using namespace Cesame;

ColorRange::ColorRange(double inMin, double inMax, QColor inColor)
{
    min = inMin;
    max = inMax;
    color = inColor;
}


QColor ColorList::interpret(double value)
{
    for(int i = 0; i < size(); i++)
    {
        if(value > at(i).min && value <= at(i).max)
        {
            return at(i).color;
        }
    }

    return CESAME_COLOR_DEFAULT;
}
