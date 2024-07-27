#include "Bar.h"

#include <iostream>
#include <QPainter>

#include "Monitor.h"
#include "TimeManager.h"


namespace Cesame {
Bar::Bar(QWidget* parent, const MetricType metricType, const double maxValue) : QWidget{parent},
    metricType(metricType),
    maxValue(maxValue) {
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, QOverload<>::of(&QWidget::repaint));
    globalTimeManager.start();
}

void Bar::paintEvent(QPaintEvent* event) {
    // Initialize Painter
    QPainter painter;
    painter.begin(this);

    // Initialize Pen and Brush
    QPen pen;
    const QBrush brush(QColor::fromRgb(255, 255, 255));
    pen.setBrush(brush);

    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidthF(1);

    painter.setPen(pen);

    // Draw border rectrangle
    // Margins are used to avoid having half of the rectangle hidden.
    painter.drawRect(contentsRect().marginsRemoved(QMargins(0, 0, 1, 1)));

    // Get the value of the metric.
    const double value = getValue().value_or(0);
    const double height = value / maxValue * contentsRect().height();

    // Draw the bar representing the value.
    const QRectF bar = QRectF(contentsRect().left(), contentsRect().bottom() - height, contentsRect().width(),
                              height);
    painter.fillRect(bar, brush);

    painter.end();
}

std::optional<double> Bar::getValue() const {
    const Metric metric = Monitor::getMetric(metricType);

    if (std::holds_alternative<double>(metric))
        return std::optional{std::get<double>(metric)};

    if (std::holds_alternative<int>(metric))
        return std::optional{static_cast<double>(std::get<int>(metric))};

    return std::nullopt;
}
}
