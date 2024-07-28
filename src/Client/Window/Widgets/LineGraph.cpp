#include "LineGraph.h"

#include <QPainter>

#include "Metric.h"
#include "Monitor.h"
#include "TimeManager.h"

Cesame::LineGraphElement::LineGraphElement(const MetricType metricType, const double maxValue, const double minValue) :
    metricType(metricType),
    maxValue(maxValue),
    minValue(minValue) {}

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
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, &LineGraph::updateData);
    globalTimeManager.start();

    /*std::cout << "Beginning painter." << std::endl;
    painter.begin(this);
    std::cout << "Painter has begun." << std::endl;
    */
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
    painter.drawRect(contentsRect().marginsRemoved(QMargins(0, 0, 1, 1)));

    // For each element (each line of the graph)
    for (auto& element : elements) {
        QPolygonF polygon;

        // For each data point of the current element
        for (int i = 0; i < element.dataPoints.size(); i++) {
            // Find the height of the current data point on the graph.
            double y = contentsRect().height() - element.dataPoints.at(i) * contentsRect().height() / element.
                maxValue;

            // Clamp the height of the point to the limits of the graph.
            y = std::clamp(y, 0.0, static_cast<double>(contentsRect().height()));

            // Find the horizontal position of t he current data point on the graph.
            const double x = contentsRect().width() - static_cast<double>(i * contentsRect().width()) / nbDataPoints;

            polygon << QPointF(x, y);
        }

        painter.drawPolyline(polygon);
    }
}

