#include "LineGraph.h"

#include <QPainter>
#include <utility>

#include "Metric.h"
#include "Monitor.h"
#include "StyleManager.h"
#include "TimeManager.h"

Cesame::LineGraphElement::LineGraphElement(const MetricType metricType, const double maxValue, const double minValue,
                                           ColorRangeList colorRanges) :
    metricType(metricType),
    maxValue(maxValue),
    minValue(minValue),
    colorRanges(std::move(colorRanges)) {}

void Cesame::LineGraphElement::update(const unsigned int nbDataPoints) {
    // Get the value from the Monitor, or fail if the value is not a number.
    const double value = metricToDouble(Monitor::getMetric(metricType)).value();

    // Update the array of data points.
    dataPoints.push_front(value);
    if (dataPoints.size() > nbDataPoints)
        dataPoints.pop_back();
}

Cesame::LineGraph::LineGraph(QWidget* parent, const QList<LineGraphElement>& elements, const unsigned int nbDataPoints):
    QWidget{parent},
    elements(elements),
    nbDataPoints(nbDataPoints) {
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, // NOLINT(*-unused-return-value)
            &LineGraph::updateData);
    globalTimeManager.start();
}

void Cesame::LineGraph::updateData() {
    for (auto& element : elements)
        element.update(nbDataPoints);

    repaint();
}

void Cesame::LineGraph::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    // Initialize pen and brush.
    QPen pen;
    pen.setWidthF(1);
    pen.setColor(QColor::fromRgb(255, 255, 255));
    painter.setPen(pen);

    // Draw outline rectangle
    pen.setColor(findColor(elements.front(), elements.front().dataPoints.front()));
    painter.setPen(pen);
    painter.drawRect(contentsRect().marginsRemoved(QMargins(0, 0, 1, 1)));

    // For each element (each line of the graph)
    for (auto& element : elements) {
        QPointF lastPoint(0, 0);

        // For each data point of the current element
        // FIXME: Lots of invariants to hoist out of here.
        for (int i = 0; i < element.dataPoints.size(); i++) {
            const double currentValue = element.dataPoints.at(i);

            pen.setColor(findColor(element, currentValue));
            painter.setPen(pen);

            // Find the height of the current data point on the graph.
            double y = contentsRect().height() - currentValue * contentsRect().height() / element.maxValue;

            // Clamp the height of the point to the limits of the graph.
            y = std::clamp(y, 0.0, static_cast<double>(contentsRect().height()));

            // Find the horizontal position of the current data point on the graph.
            // FIXME: Do we need to compute that for every point? It seems to be the same.
            const double x = contentsRect().width() - static_cast<double>(i * contentsRect().width()) / nbDataPoints;

            QPointF currentPoint(x, y);

            if (!lastPoint.isNull())
                painter.drawLine(lastPoint, currentPoint);

            lastPoint = currentPoint;
        }
    }
}

// FIXME: Seems like suboptimal syntax here.
QColor Cesame::LineGraph::findColor(const LineGraphElement& element, const double value) {
    if (!element.colorRanges.isEmpty())
        return element.colorRanges.getColor(value);

    // TODO: Use proper default color system, this will fail if the palette uses a different naming scheme.
    return StyleManager::getInstance().getDefaultPalette().getColor("white4");
}

