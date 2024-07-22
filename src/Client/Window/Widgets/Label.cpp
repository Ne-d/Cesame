#include "Label.h"

#include <iostream>
#include <QTimer>

namespace Cesame {
Label::Label(QWidget* parent, const QList<LabelElement>& elements) : QLabel{parent},
                                                                     elements(elements) {
    connect(&timer, &QTimer::timeout, this, &Label::updateText);
    timer.setInterval(std::chrono::milliseconds(1000));
    timer.setSingleShot(false);
    timer.start();

    updateText();
}

void Label::updateText() {
    setText(buildString());
}

QString Label::metricToString(const Metric& metric) {
    if (std::holds_alternative<double>(metric))
        return formatNumber(std::get<double>(metric));

    if (std::holds_alternative<int>(metric))
        return formatNumber(std::get<int>(metric));

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
    std::ostringstream str;
    str << std::fixed;
    str << std::setprecision(2);
    str << number;
    return QString::fromStdString(str.str());
}
}


