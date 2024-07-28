#include "Bar.h"

#include <QPainter>

#include "Monitor.h"
#include "TimeManager.h"


namespace Cesame {
Bar::Bar(QWidget* parent, const MetricType metricType, const double maxValue) : QWidget{parent},
    metricType(metricType),
    value(0),
    maxValue(maxValue) {
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, &Bar::updateData);
    globalTimeManager.start();

    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void Bar::updateData() {
    value = metricToDouble(Monitor::getMetric(metricType)).value_or(0);
    repaint();
}

void Bar::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    // Initialize Painter
    QPainter painter(this);

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
    const double height = value / maxValue * contentsRect().height();

    // Draw the bar representing the value.
    const QRectF bar = QRectF(contentsRect().left(), contentsRect().bottom() - height, contentsRect().width(),
                              height);
    painter.fillRect(bar, brush);
}
}
