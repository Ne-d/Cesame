#include "ColorRange.h"

#include <list>

namespace Cesame {
// ColorRange Class

ColorRange::ColorRange(const double lowerBound, const double upperBound, const QColor color) :
    lowerBound(lowerBound),
    upperBound(upperBound),
    color(color) {}

double ColorRange::getLowerBound() const {
    return lowerBound;
}

void ColorRange::setLowerBound(const double lowerBound) {
    this->lowerBound = lowerBound;
}

double ColorRange::getUpperBound() const {
    return upperBound;
}

void ColorRange::setUpperBound(const double upperBound) {
    this->upperBound = upperBound;
}

QColor ColorRange::getColor() const {
    return color;
}

void ColorRange::setColor(const QColor& color) {
    this->color = color;
}


// ColorRangeList Class

ColorRangeList::ColorRangeList(QList<ColorRange> list) : colorRanges(std::move(list)) {}

std::optional<QColor> ColorRangeList::getColor(const double value) const {
    if (colorRanges.empty())
        return std::nullopt;

    const ColorRange& firstRange = colorRanges.constFirst();
    const ColorRange& lastRange = colorRanges.constLast();

    if (value < firstRange.getLowerBound())
        return colorRanges.constFirst().getColor();

    if (value >= lastRange.getUpperBound())
        return colorRanges.constLast().getColor();

    for (const ColorRange& range : colorRanges) {
        // If the value is within the bounds of the ColorRange
        if (range.getLowerBound() <= value && range.getUpperBound() > value) {
            return range.getColor();
        }
    }

    return firstRange.getColor();
}
} // Cesame
