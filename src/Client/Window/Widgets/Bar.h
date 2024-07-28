#ifndef BAR_H
#define BAR_H

#include <QWidget>

#include "MetricType.h"

namespace Cesame {
class Bar final : public QWidget {
    Q_OBJECT

public: // Methods
    explicit Bar(QWidget* parent, MetricType metricType, double maxValue);

public slots:
    void updateData();
    void paintEvent(QPaintEvent* event) override;

private: // Data
    MetricType metricType;
    double value{};
    double maxValue;
};
}

#endif //BAR_H
