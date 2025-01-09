#include "Label.h"

#include <QPainter>
#include <QTimer>
#include <utility>

#include "TimeManager.h"

namespace Cesame {
Label::Label(QWidget* parent, const QList<LabelElement>& elements, ColorRangeList colorRanges,
             const unsigned int colorRangeElementIndex) :
    QWidget{parent},
    elements(elements),
    colorRanges(std::move(colorRanges)),
    colorRangeElementIndex(colorRangeElementIndex) {
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, &Label::updateText);

    // TODO: Use proper styling.
    font.setPixelSize(26);
    setMinimumHeight(static_cast<int>(font.pixelSize() * 1.4));

    // Start the global timer in case it wasn't done already.
    globalTimeManager.start();

    repaint();
}

void Label::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPen pen;

    QColor color = QColor::fromRgb(255, 255, 255);

    if (elements.size() >= colorRangeElementIndex && !colorRanges.isEmpty()) {
        if (std::holds_alternative<MetricType>(elements.at(colorRangeElementIndex))) {
            const MetricType type = std::get<MetricType>(elements.at(colorRangeElementIndex));
            color = colorRanges.getColor(std::get<double>(Monitor::getMetric(type)));
        }
    }

    pen.setColor(color);
    painter.setPen(pen);

    painter.setFont(font);

    painter.drawText(contentsRect(), buildString());
}

void Label::updateText() {
    update();
}

QString Label::metricToString(const Metric& metric) {
    if (std::holds_alternative<double>(metric))
        return formatNumber(std::get<double>(metric));

    if (std::holds_alternative<std::string>(metric))
        return QString::fromStdString(std::get<std::string>(metric));

    return {"?"};
}

QString Label::buildString() {
    QString string;

    // For every label element in the list.
    for (const LabelElement& element : elements) {
        // If the element is a Metric Type.
        if (std::holds_alternative<MetricType>(element)) {
            MetricType metric = std::get<MetricType>(element);

            // Add the value of the metric to the string we are building.
            string += metricToString(Monitor::getMetric(metric));
        }

        // If the element is a string.
        else
        // Add the string to the main string we are building.
            string += std::get<QString>(element);
    }

    return string;
}

QString Label::formatNumber(const double number) {
    return QString::fromStdString(std::format("{:0>5.2f}", number));
}
}


