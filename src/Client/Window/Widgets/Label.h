#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <QTimer>

#include "ColorRange.h"
#include "Metric.h"
#include "MetricType.h"
#include "Monitor.h"

namespace Cesame {
using LabelElement = std::variant<MetricType, QString>;

class Label final : public QLabel {
    Q_OBJECT

public:
    explicit Label(QWidget* parent, const QList<LabelElement>& elements, unsigned int colorRangeElementIndex = 0);

public slots:
    void updateText();

private: // Helper methods
    static QString metricToString(const Metric& metric);
    QString buildString(const QColor& color);
    static QString formatNumber(double number);

private: // Data
    QList<LabelElement> elements;
    ColorRangeList colorRanges;
    unsigned int colorRangeElementIndex;
    QColor color;
};
} // Cesame

#endif //LABEL_H
