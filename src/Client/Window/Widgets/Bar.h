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
    void paintEvent(QPaintEvent* event) override;

private: // Helper methods
    [[nodiscard]] std::optional<double> getValue() const;

private: // Data
    MetricType metricType;
    double maxValue;
};
}

#endif //BAR_H
