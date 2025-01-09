#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <deque>
#include <QPainter>

#include "ColorRange.h"
#include "MainWidget.h"
#include "MetricType.h"

namespace Cesame {
class LineGraphElement {
public: // Methods
    LineGraphElement(MetricType metricType, double maxValue, double minValue = 0,
                     ColorRangeList colorRanges = ColorRangeList(QList<ColorRange>()));

    /**
     * Updates the list of data points with a new value from the Monitor.
     * Only keeps up to size data points.
     *
     * @param nbDataPoints The maximum size of the list of data points.
     */
    void update(unsigned int nbDataPoints);

public: // This is basically a struct so the fields are public because why the fuck would I use accessors here?
    MetricType metricType;

    double maxValue;
    double minValue = 0;

    ColorRangeList colorRanges;

    std::deque<double> dataPoints;
};

class LineGraph final : public QWidget {
    Q_OBJECT

public: // Methods
    LineGraph(QWidget* parent, const QList<LineGraphElement>& elements, unsigned int nbDataPoints);

public slots:
    void updateData();
    void paintEvent(QPaintEvent* event) override;

private: // Methods
    static QColor findColor(const LineGraphElement& element, double value);

private: // Data
    QList<LineGraphElement> elements;
    unsigned int nbDataPoints;
};
}
#endif //LINEGRAPH_H
