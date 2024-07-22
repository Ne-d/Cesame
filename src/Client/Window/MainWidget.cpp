#include "MainWidget.h"

#include <QStyle>

#include "Label.h"

namespace Cesame {
MainWidget::MainWidget() {
    // TODO: Use proper styling.
    setStyleSheet("background-color: #00000000");

    auto* label = new Label(this, {"CPU Usage: ", MetricType(CpuUsageRateAverage), "%"});
    label->show();
}
}
