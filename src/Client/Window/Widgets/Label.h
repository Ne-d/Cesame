#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <QTimer>

#include "Metric.h"
#include "MetricType.h"
#include "Monitor.h"

namespace Cesame {
using LabelElement = std::variant<MetricType, QString>;

class Label final : public QLabel {
    Q_OBJECT

public:
    explicit Label(QWidget* parent, const QList<LabelElement>& elements);

public slots:
    void updateText();

private: // Helper methods
    static QString metricToString(const Metric& metric);
    QString buildString();
    static QString formatNumber(double number);

private: // Data
    QList<LabelElement> elements;

    // For testing purposes
    QTimer timer;
};
} // Cesame

#endif //LABEL_H
