#ifndef COLORRANGE_H
#define COLORRANGE_H

#include <QColor>

namespace Cesame {
/**
 * Represents a relation between a range of values and a color.
 * This can be used to set "alarm colors" for values that are too high, for example.
 */
class ColorRange {
public:
    ColorRange(double lowerBound, double upperBound, QColor color);

    // Accessors
    [[nodiscard]] double getLowerBound() const;
    void setLowerBound(double lowerBound);

    [[nodiscard]] double getUpperBound() const;
    void setUpperBound(double upperBound);

    [[nodiscard]] QColor getColor() const;
    void setColor(const QColor& color);

private:
    double lowerBound;
    double upperBound;
    QColor color;
};

/**
 * Represents a list of ColorRanges, giving access to the desired color for any value.
 */
class ColorRangeList {
public:
    explicit ColorRangeList(QList<ColorRange> list);
    [[nodiscard]] QColor getColor(double value) const;

    [[nodiscard]] bool isEmpty() const;

private:
    QList<ColorRange> colorRanges;
};
} // Cesame

#endif //COLORRANGE_H
