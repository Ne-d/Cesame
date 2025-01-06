#include "Label.h"

#include <QTimer>

#include "TimeManager.h"

namespace Cesame {
Label::Label(QWidget* parent, const QList<LabelElement>& elements, const unsigned int colorRangeElementIndex) :
    QLabel{parent},
    elements(elements),
    colorRanges({}),
    colorRangeElementIndex(colorRangeElementIndex) {
    // NOLINT(*-unused-return-value)
    connect(&globalTimeManager.getTimer(), &QTimer::timeout, this, &Label::updateText);

    // TODO: Use proper styling.
    setFont(QFont("mono", 11));

    // Start the global timer in case it wasn't done already.
    globalTimeManager.start();

    updateText();
}

void Label::updateText() {
    if (elements.size() >= colorRangeElementIndex && !colorRanges.isEmpty())
        if (std::holds_alternative<MetricType>(elements.at(colorRangeElementIndex))) {
            const MetricType type = std::get<MetricType>(elements.at(colorRangeElementIndex));
            color = colorRanges.getColor(std::get<double>(Monitor::getMetric(type)));
        }

    setText(buildString(color));
}

QString Label::metricToString(const Metric& metric) {
    if (std::holds_alternative<double>(metric))
        return formatNumber(std::get<double>(metric));

    if (std::holds_alternative<std::string>(metric))
        return QString::fromStdString(std::get<std::string>(metric));

    return {"?"};
}

QString Label::buildString(const QColor& color) {
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


