#ifndef BAR_H
#define BAR_H

#include <QWidget>

#include "MetricType.h"
#include "ColorRange.h"

namespace Cesame {
class Bar final : public QWidget {
    Q_OBJECT

public: // Methods
    explicit Bar(QWidget* parent, MetricType metricType, double maxValue, ColorRangeList colorRanges);

public slots:
    void updateData();
    void paintEvent(QPaintEvent* event) override;

private: // Data
    MetricType metricType;
    double value{};
    double maxValue;
    ColorRangeList colorRanges;
};
}

#endif //BAR_H
